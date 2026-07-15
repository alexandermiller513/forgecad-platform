# Copyright (c) 2026 Fintel IT Solutions LLC. All Rights Reserved.

"""Ollama local model integration for on-premise CAD agents."""

from typing import Protocol


class LocalLLMProvider(Protocol):
    async def generate(self, model: str, prompt: str) -> str: ...


class OllamaAgent:
    """Local LLM agent using Ollama for air-gapped deployments."""

    def __init__(self, provider: LocalLLMProvider, model: str = "llama3") -> None:
        self._provider = provider
        self._model = model

    async def run(self, prompt: str) -> str:
        return await self._provider.generate(self._model, prompt)
