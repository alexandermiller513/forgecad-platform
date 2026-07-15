# Copyright (c) 2026 Fintel IT Solutions LLC. All Rights Reserved.

"""Natural language and domain-specific CAD grammar definitions."""

from dataclasses import dataclass
from enum import Enum


class GeometryOp(Enum):
    EXTRUDE = "extrude"
    REVOLVE = "revolve"
    FILLET = "fillet"
    BOOLEAN_UNION = "boolean_union"
    BOOLEAN_SUBTRACT = "boolean_subtract"


@dataclass(frozen=True)
class GeometryInstruction:
    operation: GeometryOp
    parameters: dict[str, float | str]
    target: str | None = None
