# Copyright (c) 2026 Fintel IT Solutions LLC. All Rights Reserved.

"""LLM orchestration and agent coordination for CAD engineering tasks."""

from enum import Enum


class AgentType(Enum):
    CAD_REASONING = "cad_reasoning"
    DESIGN_OPTIMIZATION = "design_optimization"
    MANUFACTURING = "manufacturing"
    VALIDATION = "validation"


class AgentOrchestrator:
    """Coordinates LLM-backed agents for autonomous CAD workflows."""

    def __init__(self) -> None:
        self._agents: dict[AgentType, object] = {}

    def register_agent(self, agent_type: AgentType, agent: object) -> None:
        self._agents[agent_type] = agent

    async def dispatch(self, agent_type: AgentType, prompt: str) -> str:
        if agent_type not in self._agents:
            raise ValueError(f"No agent registered for {agent_type.value}")
        agent = self._agents[agent_type]
        return await agent.run(prompt)  # type: ignore[attr-defined]
