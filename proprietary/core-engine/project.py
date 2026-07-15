# Copyright (c) 2026 Fintel IT Solutions LLC. All Rights Reserved.

"""CAD project management and design lifecycle."""

from dataclasses import dataclass, field
from datetime import datetime, timezone
from uuid import uuid4


@dataclass
class CADProject:
    id: str = field(default_factory=lambda: str(uuid4()))
    name: str = "Untitled"
    created_at: datetime = field(default_factory=lambda: datetime.now(timezone.utc))
    version: int = 1


class ProjectManager:
    """Manages CAD projects, versioning, and design lifecycle."""

    def __init__(self) -> None:
        self._projects: dict[str, CADProject] = {}

    def create_project(self, name: str) -> CADProject:
        project = CADProject(name=name)
        self._projects[project.id] = project
        return project

    def get_project(self, project_id: str) -> CADProject | None:
        return self._projects.get(project_id)
