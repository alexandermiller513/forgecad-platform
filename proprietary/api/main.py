# Copyright (c) 2026 Fintel IT Solutions LLC. All Rights Reserved.

"""FastAPI backend for Fintel IT ForgeCAD."""

from fastapi import FastAPI
from pydantic import BaseModel

app = FastAPI(
    title="Fintel IT ForgeCAD API",
    description="Autonomous AI Engineering CAD Platform",
    version="0.1.0",
)


class HealthResponse(BaseModel):
    status: str
    service: str


@app.get("/health", response_model=HealthResponse)
async def health() -> HealthResponse:
    return HealthResponse(status="ok", service="forgecad-api")
