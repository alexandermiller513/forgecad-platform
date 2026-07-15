// Copyright (c) 2026 Fintel IT Solutions LLC. All Rights Reserved.

#include "forgecad/occt_adapter.hpp"

namespace forgecad::occt {

class OCCTAdapterImpl : public OCCTAdapter {
public:
    SolidHandle create_box(double dx, double dy, double dz) override;
    SolidHandle extrude(const SolidHandle& profile, double depth) override;
    bool export_step(const SolidHandle& solid, const std::string& path) override;
    bool export_brep(const SolidHandle& solid, const std::string& path) override;
};

SolidHandle OCCTAdapterImpl::create_box(double /*dx*/, double /*dy*/, double /*dz*/) {
    return SolidHandle{nullptr};
}

SolidHandle OCCTAdapterImpl::extrude(const SolidHandle& /*profile*/, double /*depth*/) {
    return SolidHandle{nullptr};
}

bool OCCTAdapterImpl::export_step(const SolidHandle& /*solid*/, const std::string& /*path*/) {
    return false;
}

bool OCCTAdapterImpl::export_brep(const SolidHandle& /*solid*/, const std::string& /*path*/) {
    return false;
}

std::unique_ptr<OCCTAdapter> create_occt_adapter() {
    return std::make_unique<OCCTAdapterImpl>();
}

}  // namespace forgecad::occt
