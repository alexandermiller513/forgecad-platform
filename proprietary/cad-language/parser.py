# Copyright (c) 2026 Fintel IT Solutions LLC. All Rights Reserved.

"""CAD domain-specific language parser."""

from .grammar import GeometryInstruction


class CADParser:
    """Parses natural language and DSL input into geometry instructions."""

    def parse(self, source: str) -> list[GeometryInstruction]:
        raise NotImplementedError("CAD parser implementation pending")
