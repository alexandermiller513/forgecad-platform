// Copyright (c) 2026 Fintel IT Solutions LLC. All Rights Reserved.

#include "forgecad/occt_adapter.hpp"
#include "forgecad/occt_shape.hpp"

#include <BRepPrimAPI_MakeBox.hxx>
#include <BRepPrimAPI_MakeCylinder.hxx>
#include <BRepPrimAPI_MakeSphere.hxx>
#include <BRepTools.hxx>
#include <BRep_Builder.hxx>
#include <IFSelect_ReturnStatus.hxx>
#include <STEPControl_Writer.hxx>
#include <TopoDS_Shape.hxx>

#include <stdexcept>

namespace forgecad::occt {
namespace {

TopoDS_Shape* as_shape_ptr(SolidHandle solid) {
    return static_cast<TopoDS_Shape*>(solid.native_handle);
}

SolidHandle wrap_shape(const TopoDS_Shape& shape) {
    if (shape.IsNull()) {
        return SolidHandle{nullptr};
    }
    return SolidHandle{new TopoDS_Shape(shape)};
}

}  // namespace

TopoDS_Shape shape_of(SolidHandle solid) {
    if (!solid) {
        return TopoDS_Shape();
    }
    return *as_shape_ptr(solid);
}

class OCCTAdapterImpl : public OCCTAdapter {
public:
    SolidHandle create_box(double dx, double dy, double dz) override {
        if (dx <= 0.0 || dy <= 0.0 || dz <= 0.0) {
            return SolidHandle{nullptr};
        }
        return wrap_shape(BRepPrimAPI_MakeBox(dx, dy, dz).Shape());
    }

    SolidHandle create_cylinder(double radius, double height) override {
        if (radius <= 0.0 || height <= 0.0) {
            return SolidHandle{nullptr};
        }
        return wrap_shape(BRepPrimAPI_MakeCylinder(radius, height).Shape());
    }

    SolidHandle create_sphere(double radius) override {
        if (radius <= 0.0) {
            return SolidHandle{nullptr};
        }
        return wrap_shape(BRepPrimAPI_MakeSphere(radius).Shape());
    }

    SolidHandle extrude(const SolidHandle& /*profile*/, double /*depth*/) override {
        // Profile-based extrusion is reserved for a later milestone.
        return SolidHandle{nullptr};
    }

    bool export_step(const SolidHandle& solid, const std::string& path) override {
        if (!solid || path.empty()) {
            return false;
        }
        STEPControl_Writer writer;
        const IFSelect_ReturnStatus status =
            writer.Transfer(*as_shape_ptr(solid), STEPControl_AsIs);
        if (status != IFSelect_RetDone) {
            return false;
        }
        return writer.Write(path.c_str()) == IFSelect_RetDone;
    }

    bool export_brep(const SolidHandle& solid, const std::string& path) override {
        if (!solid || path.empty()) {
            return false;
        }
        return BRepTools::Write(*as_shape_ptr(solid), path.c_str());
    }

    void release(SolidHandle& solid) override {
        if (solid) {
            delete as_shape_ptr(solid);
            solid.native_handle = nullptr;
        }
    }
};

std::unique_ptr<OCCTAdapter> create_occt_adapter() {
    return std::make_unique<OCCTAdapterImpl>();
}

}  // namespace forgecad::occt
