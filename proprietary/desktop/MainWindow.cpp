// Copyright (c) 2026 Fintel IT Solutions LLC. All Rights Reserved.

#include "MainWindow.h"
#include "OccView.h"

#include <QAction>
#include <QFileDialog>
#include <QMenuBar>
#include <QMessageBox>
#include <QStatusBar>
#include <QToolBar>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , m_adapter(forgecad::occt::create_occt_adapter()) {
    setWindowTitle(QStringLiteral("Fintel IT ForgeCAD"));
    resize(1280, 800);
    buildUi();
    statusBar()->showMessage(
        QStringLiteral("Left-drag orbit · Right/middle-drag pan · Scroll zoom"));
}

void MainWindow::buildUi() {
    m_view = new OccView(this);
    setCentralWidget(m_view);

    auto* toolbar = addToolBar(QStringLiteral("Modeling"));
    toolbar->setMovable(false);

    auto* actBox = toolbar->addAction(QStringLiteral("Box"), this, &MainWindow::onCreateBox);
    actBox->setToolTip(QStringLiteral("Create a box solid"));
    auto* actCyl =
        toolbar->addAction(QStringLiteral("Cylinder"), this, &MainWindow::onCreateCylinder);
    actCyl->setToolTip(QStringLiteral("Create a cylinder solid"));
    auto* actSph =
        toolbar->addAction(QStringLiteral("Sphere"), this, &MainWindow::onCreateSphere);
    actSph->setToolTip(QStringLiteral("Create a sphere solid"));
    toolbar->addSeparator();
    toolbar->addAction(QStringLiteral("Fit All"), this, &MainWindow::onFitAll);
    toolbar->addAction(QStringLiteral("Export STEP"), this, &MainWindow::onExportStep);

    auto* fileMenu = menuBar()->addMenu(QStringLiteral("&File"));
    fileMenu->addAction(QStringLiteral("Export STEP…"), this, &MainWindow::onExportStep);
    fileMenu->addSeparator();
    fileMenu->addAction(QStringLiteral("Quit"), this, &QWidget::close);

    auto* createMenu = menuBar()->addMenu(QStringLiteral("&Create"));
    createMenu->addAction(QStringLiteral("Box"), this, &MainWindow::onCreateBox);
    createMenu->addAction(QStringLiteral("Cylinder"), this, &MainWindow::onCreateCylinder);
    createMenu->addAction(QStringLiteral("Sphere"), this, &MainWindow::onCreateSphere);

    auto* viewMenu = menuBar()->addMenu(QStringLiteral("&View"));
    viewMenu->addAction(QStringLiteral("Fit All"), this, &MainWindow::onFitAll);
}

void MainWindow::onCreateBox() {
    auto solid = m_adapter->create_box(50.0, 30.0, 20.0);
    m_view->displaySolid(solid);
    statusBar()->showMessage(QStringLiteral("Created box 50 × 30 × 20"), 3000);
}

void MainWindow::onCreateCylinder() {
    auto solid = m_adapter->create_cylinder(15.0, 40.0);
    m_view->displaySolid(solid);
    statusBar()->showMessage(QStringLiteral("Created cylinder r=15 h=40"), 3000);
}

void MainWindow::onCreateSphere() {
    auto solid = m_adapter->create_sphere(20.0);
    m_view->displaySolid(solid);
    statusBar()->showMessage(QStringLiteral("Created sphere r=20"), 3000);
}

void MainWindow::onExportStep() {
    auto solid = m_view->lastSolid();
    if (!solid) {
        QMessageBox::information(
            this,
            QStringLiteral("Export STEP"),
            QStringLiteral("Create a solid first, then export."));
        return;
    }
    const QString path = QFileDialog::getSaveFileName(
        this,
        QStringLiteral("Export STEP"),
        QStringLiteral("model.step"),
        QStringLiteral("STEP Files (*.step *.stp)"));
    if (path.isEmpty()) {
        return;
    }
    if (m_adapter->export_step(solid, path.toStdString())) {
        statusBar()->showMessage(QStringLiteral("Exported %1").arg(path), 4000);
    } else {
        QMessageBox::warning(this, QStringLiteral("Export STEP"), QStringLiteral("Export failed."));
    }
}

void MainWindow::onFitAll() {
    m_view->fitAll();
}
