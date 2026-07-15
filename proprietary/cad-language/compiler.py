# Copyright (c) 2026 Fintel IT Solutions LLC. All Rights Reserved.

"""CAD language compiler — transforms parsed instructions into engine commands."""

from .grammar import GeometryInstruction


class CADCompiler:
    """Compiles geometry instructions into executable CAD operations."""

    def compile(self, instructions: list[GeometryInstruction]) -> list[dict]:
        return [
            {"op": instr.operation.value, "params": instr.parameters, "target": instr.target}
            for instr in instructions
        ]
