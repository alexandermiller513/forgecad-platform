# Copyright (c) 2026 Fintel IT Solutions LLC. All Rights Reserved.

"""Integration tests for Fintel ForgeCAD platform layers."""

import importlib.util
import sys
from pathlib import Path


def _load_module(name: str, path: Path):
    spec = importlib.util.spec_from_file_location(name, path)
    module = importlib.util.module_from_spec(spec)
    sys.modules[name] = module
    spec.loader.exec_module(module)
    return module


REPO_ROOT = Path(__file__).resolve().parent.parent


def test_core_engine_project_creation():
    project_mod = _load_module(
        "core_project",
        REPO_ROOT / "proprietary/core-engine/project.py",
    )
    manager = project_mod.ProjectManager()
    project = manager.create_project("Test Bracket")
    assert project.name == "Test Bracket"
    assert manager.get_project(project.id) is project


def test_cad_language_compiler():
    grammar = _load_module(
        "cad_grammar",
        REPO_ROOT / "proprietary/cad-language/grammar.py",
    )
    compiler = _load_module(
        "cad_compiler",
        REPO_ROOT / "proprietary/cad-language/compiler.py",
    )
    instr = grammar.GeometryInstruction(
        operation=grammar.GeometryOp.EXTRUDE,
        parameters={"depth": 10.0},
    )
    result = compiler.CADCompiler().compile([instr])
    assert result[0]["op"] == "extrude"
    assert result[0]["params"]["depth"] == 10.0
