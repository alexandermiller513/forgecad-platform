// Copyright (c) 2026 Fintel IT Solutions LLC. All Rights Reserved.

#pragma once

#include "forgecad/occt_adapter.hpp"

#include <TopoDS_Shape.hxx>

namespace forgecad::occt {

/// Returns a copy of the TopoDS_Shape owned by the handle (null shape if invalid).
TopoDS_Shape shape_of(SolidHandle solid);

}  // namespace forgecad::occt
