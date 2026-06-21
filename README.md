# 2D Action-RPG Engine (C++ / SFML)

A custom 2D RPG engine and game built from scratch in C++ using SFML, featuring a component-based entity system, a finite state machine for game flow, a fully custom GUI toolkit, and an in-game tile-based level editor with file save/load support.

No game engine (Unity, Unreal, Godot) was used — rendering, input, animation, physics, AI, and UI are all hand-built on top of SFML's low-level primitives.

---

https://github.com/user-attachments/assets/ecfd14b9-e45b-4c0e-9f8e-4a0265790cc5

---

## Highlights

- **Component-based entity architecture** — entities (`Player`, `Enemy`) are composed from independent components (`MovementComponent`, `AnimationComponent`, `HitboxComponent`, `HealthComponent`, `DamageComponent`, `RotationComponent`) rather than relying on deep inheritance chains.
- **Predictive combat AI** — enemies don't just chase the player. Before committing to an attack, each enemy runs a physics-based prediction: it calculates its own slide distance under deceleration, projects the player's future position from their current velocity, and checks for a future hitbox collision *and* directional alignment (via dot product) before deciding to strike.
- **Finite state machine architecture** — `MainMenuState`, `GameState`, `EditorState`, `SettingState`, and `PauseMenu` all derive from a shared `State` base class, managed through a state stack (push/pop) for clean transitions and overlays.
- **In-game level editor** — a built-in `EditorState` lets you paint tiles across multiple layers directly in the running application, with a texture-sheet picker, grid toggle, and live tile selector — no external tool required.
- **Generic layer/object manager** — `LayerManager` maintains an ordered stack of any `Obj`-derived element (tilemap, buttons, menus alike) behind a single polymorphic interface (`update`, `render`, `isMouseOver`, `reset`). Input is dispatched top-down through the stack and consumed by the first object that claims it, with everything beneath automatically reset — giving correct UI focus/hit-testing without each state having to manage z-order or input priority by hand. `pushObjToFront` / `pushObjToBack` let states reorder elements at runtime.
- **Custom binary/text tilemap format** — `TileMap::saveToFile` / `loadFromFile` serialize a full multi-layer grid (`x, y, z` tile data) to disk and back.
- **Hand-built GUI toolkit** — buttons, dropdowns, carousels, and option menus implemented from scratch (no Dear ImGui or similar), driven by the same render/update loop as the game itself.
- **Data-driven keybinds** — controls are read from `.ini` config files per state, not hardcoded.

---

## Tech Stack

| Layer | Technology |
|---|---|
| Language | C++ |
| Graphics / Windowing / Input | [SFML](https://www.sfml-dev.org/) |
| Build | Visual Studio (`.sln` / `.vcxproj`) |
| Platform | Windows |

---

## Architecture Overview

```
Game
 └─ std::stack<State*>          // active state stack (push/pop for menus, pause, etc.)
     ├─ MainMenuState
     ├─ GameState
     │   ├─ Player (Entity)
     │   ├─ Enemy (Entity)       // predictive combat AI
     │   └─ TileMap
     ├─ EditorState
     │   ├─ LayerManager          // ordered Obj stack: input dispatch + z-order
     │   │   ├─ TileMap            // paint / save / load
     │   │   └─ OptionMenu          // layer + texture picker
     │   └─ PauseMenu
     └─ SettingState

Entity
 ├─ MovementComponent
 ├─ AnimationComponent
 ├─ HitboxComponent
 ├─ HealthComponent
 ├─ DamageComponent
 └─ RotationComponent
```

Each `State` owns its own input handling, update loop, and render pass, and reports back to the shared `StateData` (window, keybinds, grid size) so new states can be added without touching the core game loop.

---

## Getting Started

### Prerequisites
- Windows
- Visual Studio (2019 or later recommended)
- SFML libraries (included under `includes/`)

### Build & Run
1. Clone the repository.
2. Open `Game-Development.sln` in Visual Studio.
3. Build the `RPG - SFML` project (Debug or Release, x86).
4. Run — the executable expects the `Resources/` and `Config/` folders alongside it (already set up via the project's working directory).

### Controls
Keybinds are defined per state in `RPG - SFML/Config/*.ini` (e.g. `gameState_Keybinds.ini`, `editorState_Keybinds.ini`) and can be edited without recompiling.

---

## Project Structure

```
RPG - SFML/
├── Config/              # keybind & graphics settings (.ini)
├── Resources/
│   ├── Images/           # sprites, backgrounds, UI textures
│   └── saves/            # serialized tilemaps (.stm)
├── *Component.*          # entity component system
├── *State.*               # game states (menu, game, editor, settings, pause)
├── GUI / Button* / *List* # custom UI widgets
├── TileMap.* / Tile.*     # map data, rendering, serialization
├── Player.* / Enemy.*     # gameplay entities
└── Game.* / State.*       # core loop & state machine
```

---

## Status & Roadmap

This is an active learning/portfolio project exploring engine architecture from first principles. Planned next steps include expanding the AI behavior tree, adding inventory/item systems, and porting the build off the Visual Studio solution toward a cross-platform CMake setup.

---

## License

No license file is currently included — all rights reserved by default.
