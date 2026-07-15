# Copyright (c) 2026 Fintel IT Solutions LLC. All Rights Reserved.

"""GPT integration for cloud-based CAD reasoning."""

from typing import Protocol


class LLMProvider(Protocol):
    async def complete(self, prompt: str, system: str | None = None) -> str: ...


class GPTAgent:
    """OpenAI GPT integration for CAD engineering agents."""

    def __init__(self, provider: LLMProvider, model: str = "gpt-4") -> None:
        self._provider = provider
        self._model = model

    async def run(self, prompt: str) -> str:
        system = "You are a CAD engineering assistant for Fintel ForgeCAD."
        return await self._provider.complete(prompt, system=system)
