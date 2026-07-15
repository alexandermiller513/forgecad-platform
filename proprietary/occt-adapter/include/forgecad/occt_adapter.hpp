// Copyright (c) 2026 Fintel IT Solutions LLC. All Rights Reserved.

#pragma once

#include <memory>
#include <string>

namespace forgecad::occt {

struct Point3D {
    double x, y, z;
};

/// Opaque handle to an OCCT TopoDS_Shape owned by the adapter layer.
struct SolidHandle {
    void* native_handle = nullptr;

    explicit operator bool() const { return native_handle != nullptr; }
};

/// Abstract interface for Open CASCADE geometry operations.
/// Proprietary adapter — does not contain OCCT source code.
class OCCTAdapter {
public:
    virtual ~OCCTAdapter() = default;

    virtual SolidHandle create_box(double dx, double dy, double dz) = 0;
    virtual SolidHandle create_cylinder(double radius, double height) = 0;
    virtual SolidHandle create_sphere(double radius) = 0;
    virtual SolidHandle extrude(const SolidHandle& profile, double depth) = 0;
    virtual bool export_step(const SolidHandle& solid, const std::string& path) = 0;
    virtual bool export_brep(const SolidHandle& solid, const std::string& path) = 0;
    virtual void release(SolidHandle& solid) = 0;
};

std::unique_ptr<OCCTAdapter> create_occt_adapter();

}  // namespace forgecad::occt
