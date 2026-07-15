# Copyright (c) 2026 Fintel IT Solutions LLC. All Rights Reserved.

"""Data persistence for CAD projects, geometry metadata, and user sessions."""

from typing import Protocol


class DatabaseConnection(Protocol):
    async def execute(self, query: str, params: dict | None = None) -> list[dict]: ...


class ProjectRepository:
    """Persists and retrieves CAD project records."""

    def __init__(self, db: DatabaseConnection) -> None:
        self._db = db

    async def save(self, project_id: str, data: dict) -> None:
        await self._db.execute(
            "INSERT INTO projects (id, data) VALUES (:id, :data)",
            {"id": project_id, "data": data},
        )
