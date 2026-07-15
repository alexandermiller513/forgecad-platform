# Fintel ForgeCAD

Autonomous AI Engineering CAD Platform

**Copyright (c) 2026 Fintel IT Solutions LLC. All Rights Reserved.**

Fintel ForgeCAD is a proprietary autonomous CAD engineering platform developed by Fintel IT Solutions LLC. The platform combines AI-driven design agents, a domain-specific CAD language, and enterprise-grade engineering workflows.

## Architecture

Clean architecture with strict separation between proprietary and third-party code:

| Layer | Path | License |
|-------|------|---------|
| AI Agent Layer | `proprietary/ai-agents` | Proprietary |
| CAD Language Layer | `proprietary/cad-language` | Proprietary |
| OCCT Adapter Layer | `proprietary/occt-adapter` | Proprietary |
| Core Engine | `proprietary/core-engine` | Proprietary |
| API | `proprietary/api` | Proprietary |
| UI | `proprietary/ui` | Proprietary |
| Cloud Services | `proprietary/cloud-services` | Proprietary |
| Database | `proprietary/database` | Proprietary |
| Manufacturing Engine | `proprietary/manufacturing-engine` | Proprietary |
| Simulation Engine | `proprietary/simulation-engine` | Proprietary |
| Open CASCADE (OCCT) | `third-party/occt` | LGPL-2.1 |

## Third-Party Dependencies

Open CASCADE Technology is included as an external LGPL dependency under `third-party/occt`. Proprietary code must never be placed inside the OCCT source tree. See [THIRD_PARTY_LICENSES.md](THIRD_PARTY_LICENSES.md).

## Branch Strategy

- `main` — production releases
- `develop` — integration branch
- `feature/ai-agents` — AI agent development
- `feature/cad-language` — CAD language development
- `feature/occt-adapter` — OCCT adapter development

## License

Proprietary. See [LICENSE](LICENSE).
