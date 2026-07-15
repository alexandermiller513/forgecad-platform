# Copyright (c) 2026 Fintel IT Solutions LLC. All Rights Reserved.

"""Integration tests for Fintel IT ForgeCAD platform layers."""

import importlib.util
import sys
from pathlib import Path


def _load_module(name: str, path: Path):
    spec = importlib.util.spec_from_file_location(name, path)
    module = importlib.util.module_from_spec(spec)
    sys.modules[name] = module
    spec.loader.exec_module(module)
    return module


def _load_package_module(package_dir: Path, module_name: str):
    """Load a module from a hyphenated directory with working relative imports."""
    pkg_import_name = package_dir.name.replace("-", "_")
    if pkg_import_name not in sys.modules:
        pkg = importlib.util.module_from_spec(
            importlib.util.spec_from_loader(pkg_import_name, loader=None)
        )
        pkg.__path__ = [str(package_dir)]
        pkg.__package__ = pkg_import_name
        sys.modules[pkg_import_name] = pkg

    full_name = f"{pkg_import_name}.{module_name}"
    spec = importlib.util.spec_from_file_location(
        full_name,
        package_dir / f"{module_name}.py",
        submodule_search_locations=[str(package_dir)],
    )
    module = importlib.util.module_from_spec(spec)
    module.__package__ = pkg_import_name
    sys.modules[full_name] = module
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
    cad_lang_dir = REPO_ROOT / "proprietary/cad-language"
    grammar = _load_package_module(cad_lang_dir, "grammar")
    compiler = _load_package_module(cad_lang_dir, "compiler")
    instr = grammar.GeometryInstruction(
        operation=grammar.GeometryOp.EXTRUDE,
        parameters={"depth": 10.0},
    )
    result = compiler.CADCompiler().compile([instr])
    assert result[0]["op"] == "extrude"
    assert result[0]["params"]["depth"] == 10.0
