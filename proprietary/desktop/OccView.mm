// Copyright (c) 2026 Fintel IT Solutions LLC. All Rights Reserved.

#include "OccView.h"

#include <forgecad/occt_shape.hpp>

#include <AIS_Shape.hxx>
#include <AIS_Trihedron.hxx>
#include <Aspect_DisplayConnection.hxx>
#include <BRepPrimAPI_MakeBox.hxx>
#include <Geom_Axis2Placement.hxx>
#include <OpenGl_GraphicDriver.hxx>

#ifdef _WIN32
#include <WNT_Window.hxx>
#elif defined(__APPLE__)
#include <Cocoa_Window.hxx>
#else
#include <Xw_Window.hxx>
#endif

#include <QMouseEvent>
#include <QShowEvent>
#include <QWheelEvent>

OccView::OccView(QWidget* parent)
    : QWidget(parent) {
    setAttribute(Qt::WA_NativeWindow);
    setAttribute(Qt::WA_PaintOnScreen);
    setAttribute(Qt::WA_NoSystemBackground);
    setMouseTracking(true);
    setMinimumSize(400, 300);
    setFocusPolicy(Qt::StrongFocus);
}

OccView::~OccView() = default;

void OccView::showEvent(QShowEvent* event) {
    QWidget::showEvent(event);
    if (!m_initialized) {
        initViewer();
        m_initialized = true;
    }
}

void OccView::initViewer() {
    Handle(Aspect_DisplayConnection) display = new Aspect_DisplayConnection();
    Handle(OpenGl_GraphicDriver) driver = new OpenGl_GraphicDriver(display);

    m_viewer = new V3d_Viewer(driver);
    m_viewer->SetDefaultLights();
    m_viewer->SetLightOn();

    m_view = m_viewer->CreateView();
    m_context = new AIS_InteractiveContext(m_viewer);

#ifdef _WIN32
    Handle(WNT_Window) window = new WNT_Window(reinterpret_cast<Aspect_Handle>(winId()));
#elif defined(__APPLE__)
    NSView* nsView = reinterpret_cast<NSView*>(static_cast<uintptr_t>(winId()));
    Handle(Cocoa_Window) window = new Cocoa_Window(nsView);
#else
    Handle(Xw_Window) window = new Xw_Window(display, static_cast<Window>(winId()));
#endif

    m_view->SetWindow(window);
    if (!window->IsMapped()) {
        window->Map();
    }

    m_view->SetBackgroundColor(Quantity_Color(0.12, 0.14, 0.18, Quantity_TOC_RGB));
    m_view->TriedronDisplay(Aspect_TOTP_LEFT_LOWER, Quantity_NOC_GOLD, 0.08, V3d_ZBUFFER);
    m_view->MustBeResized();

    Handle(Geom_Axis2Placement) axis = new Geom_Axis2Placement(gp::XOY());
    Handle(AIS_Trihedron) triad = new AIS_Trihedron(axis);
    triad->SetSize(30.0);
    m_context->Display(triad, false);

    // Seed scene with a box so the viewport is obviously a CAD view on launch.
    TopoDS_Shape box = BRepPrimAPI_MakeBox(40.0, 25.0, 15.0).Shape();
    Handle(AIS_Shape) ais = new AIS_Shape(box);
    ais->SetColor(Quantity_NOC_SKYBLUE);
    ais->SetDisplayMode(AIS_Shaded);
    m_context->Display(ais, true);
    m_view->FitAll(0.1, false);
    m_view->ZFitAll();
    m_view->Redraw();
}

void OccView::displaySolid(forgecad::occt::SolidHandle solid) {
    if (!m_initialized || !solid) {
        return;
    }
    TopoDS_Shape shape = forgecad::occt::shape_of(solid);
    if (shape.IsNull()) {
        return;
    }
    m_lastSolid = solid;
    Handle(AIS_Shape) ais = new AIS_Shape(shape);
    ais->SetColor(Quantity_NOC_ORANGE);
    ais->SetDisplayMode(AIS_Shaded);
    m_context->Display(ais, true);
    m_view->FitAll(0.1, false);
    m_view->ZFitAll();
    m_view->Redraw();
}

void OccView::fitAll() {
    if (!m_initialized) {
        return;
    }
    m_view->FitAll(0.1, true);
}

void OccView::paintEvent(QPaintEvent*) {
    if (m_initialized && !m_view.IsNull()) {
        m_view->Redraw();
    }
}

void OccView::resizeEvent(QResizeEvent* event) {
    QWidget::resizeEvent(event);
    if (m_initialized && !m_view.IsNull()) {
        m_view->MustBeResized();
        m_view->Redraw();
    }
}

void OccView::mousePressEvent(QMouseEvent* event) {
    m_lastPos = event->pos();
    if (event->button() == Qt::LeftButton) {
        m_mode = NavMode::Rotate;
        m_view->StartRotation(event->pos().x(), event->pos().y());
    } else if (event->button() == Qt::MiddleButton || event->button() == Qt::RightButton) {
        m_mode = NavMode::Pan;
    }
}

void OccView::mouseReleaseEvent(QMouseEvent*) {
    m_mode = NavMode::None;
}

void OccView::mouseMoveEvent(QMouseEvent* event) {
    if (!m_initialized || m_mode == NavMode::None) {
        return;
    }
    const QPoint delta = event->pos() - m_lastPos;
    if (m_mode == NavMode::Rotate) {
        m_view->Rotation(event->pos().x(), event->pos().y());
    } else if (m_mode == NavMode::Pan) {
        m_view->Pan(delta.x(), -delta.y());
    }
    m_lastPos = event->pos();
    m_view->Redraw();
}

void OccView::wheelEvent(QWheelEvent* event) {
    if (!m_initialized) {
        return;
    }
    const double factor = event->angleDelta().y() > 0 ? 1.12 : 1.0 / 1.12;
    m_view->SetZoom(factor);
    m_view->Redraw();
}
