// Copyright (c) 2026 Fintel IT Solutions LLC. All Rights Reserved.

#pragma once

#include <QMainWindow>

#include <forgecad/occt_adapter.hpp>

#include <memory>

class OccView;

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = nullptr);

private slots:
    void onCreateBox();
    void onCreateCylinder();
    void onCreateSphere();
    void onExportStep();
    void onFitAll();

private:
    void buildUi();

    OccView* m_view = nullptr;
    std::unique_ptr<forgecad::occt::OCCTAdapter> m_adapter;
};
