# Copyright (c) 2026 Fintel IT Solutions LLC. All Rights Reserved.

"""Workflow orchestration for CAD design lifecycle."""

from enum import Enum


class LifecycleStage(Enum):
    DRAFT = "draft"
    IN_REVIEW = "in_review"
    APPROVED = "approved"
    MANUFACTURING = "manufacturing"
    ARCHIVED = "archived"


class WorkflowOrchestrator:
    """Orchestrates design lifecycle transitions and workflow rules."""

    def __init__(self) -> None:
        self._stage: LifecycleStage = LifecycleStage.DRAFT

    def transition(self, target: LifecycleStage) -> LifecycleStage:
        self._stage = target
        return self._stage

    @property
    def current_stage(self) -> LifecycleStage:
        return self._stage
