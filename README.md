# 🎮 Game Development Engine

A high-performance 2D game engine built from scratch using C++, featuring a robust component-based architecture designed for modular gameplay development and real-time rendering optimization.

---

## 🎯 Overview

The **Game Development Engine** is a custom-built 2D game engine developed in C++ with SFML graphics library, focusing on flexible game architecture and efficient resource management. It implements industry-standard game development patterns including a deterministic game loop, component-based entity system, and real-time rendering pipeline. Designed to support interactive and dynamic game environments with built-in UI systems, collision detection, and basic AI pathfinding.

### Key Highlights
- **Component-Based Architecture**: Flexible entity-component system for decoupled game object behavior
- **Deterministic Game Loop**: Consistent frame-rate independent gameplay across all hardware
- **Real-Time Rendering**: Optimized 2D graphics pipeline with SFML integration
- **Custom UI Engine**: Professional menu and HUD systems for game interfaces
- **Interactive Environment**: Collision detection and basic AI pathfinding for dynamic gameplay

---

## ✨ Core Features

### 🏗️ Component-Based System
- **Modular Game Objects**: Create complex entities by composing reusable components
- **Flexible Behavior Management**: Easy addition/removal of functionality without tight coupling
- **Resource Pooling**: Efficient memory management through object reuse patterns
- **Type-Safe Components**: Compile-time component safety using C++ templates

### 🎮 Game Loop & Rendering
- **Deterministic Game Loop**: Fixed timestep ensures consistent physics and gameplay across all systems
- **Frame-Rate Independent**: Smooth gameplay regardless of hardware capabilities
- **Real-Time Rendering**: 2D graphics rendering with SFML
- **Scene Management**: Multiple scene support with smooth transitions

### 🎨 UI Engine Development
- **Menu System**: Professional main menu with navigation and state management
- **HUD Rendering**: Dynamic health bars, scores, and game state displays
- **Text Rendering**: Custom font system with scalable text rendering
- **Input Handling**: Responsive keyboard and mouse input management

### 🤖 AI & Physics
- **Pathfinding Logic**: Basic AI navigation with waypoint-based movement
- **Collision Detection**: Accurate collision systems for game entities
- **Physics Simulation**: Basic velocity and acceleration systems
- **Enemy AI**: Simple state-based enemy behavior patterns

---

## 🛠️ Technology Stack

| Category | Technologies |
|----------|---|
| **Language** | C++ (C++17 Standard) |
| **Graphics Library** | SFML 2.5+ |
| **Build System** | Visual Studio 2022 / CMake |
| **Architecture Pattern** | Component-Based Entity System |
| **Rendering** | 2D Real-Time Graphics |
| **Physics** | Custom 2D Physics Simulation |

---

## 🏗️ Architecture

### Component-Based Entity System

The engine uses a flexible ECS (Entity-Component-System) pattern:

```
┌─────────────────────────────────────┐
│          Game Entity                │
├─────────────────────────────────────┤
│  ├─ Movement Component              │
│  ├─ Animation Component             │
│  ├─ Hitbox Component                │
│  ├─ Health & Damage Components      │
│  └─ And more...                     │
└─────────────────────────────────────┘
```

### Game Loop Architecture

```
Start Frame
    ↓
Input Processing
    ↓
Update Logic (Fixed Timestep)
    ↓
Collision Detection
    ↓
AI/Pathfinding
    ↓
Rendering
    ↓
End Frame
```

---

## 🎨 Design Patterns & Best Practices

### ✅ Object-Oriented Design
- **Encapsulation**: Clear component interfaces with hidden implementation
- **Inheritance Hierarchy**: Base component class with specialized derivatives
- **Polymorphism**: Virtual methods for component behavior override
- **Composition over Inheritance**: Entity composition for maximum flexibility

### 🔐 Advanced Features
- **Component Pooling**: Efficient memory allocation and reuse
- **Message Passing System**: Decoupled component communication
- **State Machines**: AI state management for entity behavior
- **Factory Pattern**: Centralized entity creation and configuration

### 🎯 Performance Optimization
- **Spatial Partitioning**: Efficient collision detection optimization
- **Resource Caching**: Pre-loaded assets for faster access
- **Batch Rendering**: Optimized sprite batch drawing
- **Update Prioritization**: Selective component update scheduling

---

## 🚀 Getting Started

### Prerequisites
- Windows 10/11
- Visual Studio 2022 or GCC/Clang with CMake
- SFML 2.5 or higher
- C++17 compliant compiler

### Installation

1. **Clone the repository**
   ```bash
   git clone https://github.com/shmuelZagah/Game-Development.git
   cd Game-Development
   ```

2. **Set up SFML**
   - Download SFML from https://www.sfml-dev.org/
   - Link SFML libraries to your project
   - Include SFML headers in your compilation

3. **Build the project**
   ```bash
   # Using Visual Studio
   Open "Game-Development.sln" and build the solution
   ```

4. **Run the game**
   ```bash
   ./GameEngine
   ```

---

## 📖 Usage Guide

### Creating a Game Entity

```cpp
// Create an entity with components
Entity player = entityManager.createEntity();
player.addComponent<TransformComponent>(x, y);
player.addComponent<SpriteComponent>("player.png");
player.addComponent<CollisionComponent>(width, height);
player.addComponent<PlayerControllerComponent>();
```

### Implementing Custom Components

```cpp
class CustomComponent : public Component {
public:
    void update(float deltaTime) override {
        // Custom update logic
    }
    
    void render(sf::RenderWindow& window) override {
        // Rendering logic
    }
};
```

### Game Loop Integration

```cpp
while (window.isOpen()) {
    handleInput();
    update(deltaTime);
    detectCollisions();
    render();
}
```

---

## 📁 Project Structure

```
Game-Development/
├── GameEngine/              # Main game project
│   ├── src/                 # Source files (.cpp)
│   ├── headers/             # Header files (.h)
│   ├── assets/              # Game assets (sprites, sounds)
│   └── main.cpp             # Entry point
├── includes/                # Shared includes
├── Game-Development.sln     # Visual Studio solution
└── README.md
```


## 🚀 Future Enhancements

- **Advanced Physics**: Gravity, velocity damping, and force simulation
- **Animation System**: Sprite sheet animation and frame-based animation
- **Sound Engine**: Audio playback and spatial audio integration
- **Particle System**: Visual effects with particle emitters
- **Level Editor**: Visual tool for level design
- **Save/Load System**: Game state persistence
- **Networking**: Multiplayer support foundation
- **Mobile Support**: SFML-based mobile game deployment

---

## 🏆 Performance Metrics

- **Target FPS**: 60 FPS (fixed timestep)
- **Memory Efficient**: Component pooling for optimal allocation
- **World Rendering**: Grid-based Tilemap system for efficient level management and rendering.
- **Interaction Logic**: Layer-based hit testing (Z-Ordering) to optimize click detection and ensure accurate UI/entity interaction.

---

## 🔒 Code Quality

- **Type-Safe Components**: Template-based component system
- **Error Handling**: Exception-safe operations with validation
- **Memory Management**: Smart pointer usage for resource cleanup
- **Code Documentation**: Comprehensive header documentation

---

## 📝 License

This project is provided as-is for educational and commercial purposes.

---

## 👤 Author

**Shmuel Zagah**

B.Sc. Computer Science Student | C++ Developer

---

## 📧 Contact & Support

For questions, feedback, or collaboration opportunities:
- **GitHub**: [@shmuelZagah](https://github.com/shmuelZagah)
- **Issues**: [GitHub Issues](https://github.com/shmuelZagah/Game-Development/issues)

---

*Last Updated: April 14, 2026*