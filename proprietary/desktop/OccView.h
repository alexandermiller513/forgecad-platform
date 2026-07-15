// Copyright (c) 2026 Fintel IT Solutions LLC. All Rights Reserved.

#pragma once

#include <QWidget>

#include <AIS_InteractiveContext.hxx>
#include <V3d_View.hxx>
#include <V3d_Viewer.hxx>

#include <forgecad/occt_adapter.hpp>

class OccView : public QWidget {
    Q_OBJECT

public:
    explicit OccView(QWidget* parent = nullptr);
    ~OccView() override;

    Handle(AIS_InteractiveContext) context() const { return m_context; }
    Handle(V3d_View) view() const { return m_view; }

    void displaySolid(forgecad::occt::SolidHandle solid);
    void fitAll();
    forgecad::occt::SolidHandle lastSolid() const { return m_lastSolid; }

protected:
    void paintEvent(QPaintEvent* event) override;
    void resizeEvent(QResizeEvent* event) override;
    void showEvent(QShowEvent* event) override;
    void mousePressEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void wheelEvent(QWheelEvent* event) override;

    QPaintEngine* paintEngine() const override { return nullptr; }

private:
    void initViewer();

    Handle(V3d_Viewer) m_viewer;
    Handle(V3d_View) m_view;
    Handle(AIS_InteractiveContext) m_context;
    bool m_initialized = false;

    enum class NavMode { None, Rotate, Pan };
    NavMode m_mode = NavMode::None;
    QPoint m_lastPos;

    forgecad::occt::SolidHandle m_lastSolid{};
};

