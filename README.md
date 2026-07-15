# Fintel IT ForgeCAD

Autonomous AI Engineering CAD Platform

**Copyright (c) 2026 Fintel IT Solutions LLC. All Rights Reserved.**

Fintel IT ForgeCAD is a proprietary autonomous CAD engineering platform developed by Fintel IT Solutions LLC. The platform combines AI-driven design agents, a domain-specific CAD language, and a native 3D CAD desktop client powered by Open CASCADE Technology.

## Desktop CAD client (primary)

The modeling UI is a **Qt 6 + OCCT** native desktop application under `proprietary/desktop`.

```bash
# One-time: build OCCT (LGPL) into build/occt-install
./scripts/build-occt.sh

# Build and launch the desktop CAD modeler
./scripts/run-desktop.sh
```

**Viewport controls:** left-drag orbit · right/middle-drag pan · scroll zoom  
**Tools:** Box, Cylinder, Sphere, Fit All, Export STEP

## Architecture

Clean architecture with strict separation between proprietary and third-party code:

| Layer | Path | License |
|-------|------|---------|
| Desktop CAD Client | `proprietary/desktop` | Proprietary |
| AI Agent Layer | `proprietary/ai-agents` | Proprietary |
| CAD Language Layer | `proprietary/cad-language` | Proprietary |
| OCCT Adapter Layer | `proprietary/occt-adapter` | Proprietary |
| Core Engine | `proprietary/core-engine` | Proprietary |
| API | `proprietary/api` | Proprietary |
| Cloud Services | `proprietary/cloud-services` | Proprietary |
| Database | `proprietary/database` | Proprietary |
| Manufacturing Engine | `proprietary/manufacturing-engine` | Proprietary |
| Simulation Engine | `proprietary/simulation-engine` | Proprietary |
| Open CASCADE (OCCT) | `third-party/occt` | LGPL-2.1 |

## Third-Party Dependencies

Open CASCADE Technology is an external LGPL dependency under `third-party/occt`. Proprietary code must never be placed inside the OCCT source tree. See [THIRD_PARTY_LICENSES.md](THIRD_PARTY_LICENSES.md).

## Optional API service

```bash
.venv/bin/uvicorn main:app --reload --app-dir proprietary/api --port 8000
```

## Branch Strategy

- `main` — production releases
- `develop` / `dev` — integration branch
- `feature/ai-agents` — AI agent development
- `feature/cad-language` — CAD language development
- `feature/occt-adapter` — OCCT adapter development

## License

Proprietary. See [LICENSE](LICENSE).
