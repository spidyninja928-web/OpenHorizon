# OPEN HORIZON - Forza Horizon 6 Competitor

A high-performance racing game engine built in modern C++ targeting console and PC platforms.

## Features

### Core Engine
- **Advanced Physics**: Realistic vehicle dynamics with tire slip, weight transfer, and suspension simulation
- **Dynamic World**: Procedurally generated terrain with LOD systems
- **Intelligent Traffic**: AI-driven traffic with path-following and collision avoidance
- **Dynamic Weather**: Real-time weather effects (rain, fog, wind)
- **Day/Night Cycle**: Full 24-hour dynamic lighting system

### Graphics
- **Modern Renderer**: OpenGL 4.6 with deferred rendering
- **Shadow Mapping**: High-quality shadows with PCF filtering
- **Post-Processing**: Motion blur, chromatic aberration, vignette effects
- **Instancing**: Optimized rendering of scenery and vegetation
- **PBR Materials**: Physically-based rendering for realistic visuals

### Gameplay
- **Vehicle Physics**: 6-speed transmission with realistic gear changes
- **Drift Mechanics**: Satisfying drift system with scoring
- **Nitro Boost**: Temporary acceleration boost with strategic usage
- **Race Modes**: Freeroam, Circuit Racing, Point-to-Point
- **Progressive Damage**: Vehicle damage affects performance

## Requirements

- C++20 compiler (MSVC 2019+, GCC 10+, Clang 11+)
- CMake 3.20+
- OpenGL 4.6 compatible GPU
- Dependencies:
  - GLFW 3.3+
  - GLEW 2.2+
  - GLM 0.9.9+
  - Bullet Physics 3.0+
  - OpenAL-soft 1.20+

## Building

```bash
mkdir build
cd build
cmake ..
cmake --build . --config Release
```

## Game Architecture

```
OpenHorizon/
├── CMakeLists.txt
├── include/
│   └── engine/
│       ├── core/          # Window, Clock, Engine loop
│       ├── physics/       # Vehicle, Physics simulation
│       ├── rendering/     # Renderer, Camera, Shaders
│       ├── audio/         # Audio engine, SFX
│       ├── input/         # Input handling
│       └── world/         # Terrain, World management
├── src/
│   ├── engine/
│   ├── game/              # GameState, RaceManager
│   └── main.cpp
├── shaders/               # GLSL shaders (TODO)
└── assets/                # Game assets (TODO)
```

## Vehicle Physics Details

### Transmission System
- **6 Gears**: Automatic gear selection based on speed
- **RPM Management**: Realistic engine RPM curve
- **Gear Shift**: Smooth transitions with brief power loss

### Handling
- **Steering Response**: Speed-dependent steering angle
- **Weight Transfer**: Dynamic grip changes during acceleration/braking
- **Suspension**: Spring-damper system with compression limits
- **Tire Grip**: Longitudinal and lateral tire friction modeling

### Drift System
- **Drift Scoring**: Points for sustained drifts
- **Handbrake**: Instant drift initiation
- **Visual Feedback**: Skid marks and smoke effects
- **Combo Multiplier**: Consecutive drifts increase score

## Rendering Pipeline

1. **Shadow Pass**: Render scene from light perspective
2. **Geometry Pass**: Render all opaque objects with deferred shading
3. **Lighting Pass**: Apply dynamic and static lights
4. **Transparency**: Render transparent objects (glass, particles)
5. **Post-Processing**: Apply motion blur, chromatic aberration, vignette
6. **UI**: Overlay HUD elements

## Performance Targets

- **PC (High)**: 1440p @ 144 FPS (RTX 4070+)
- **PC (Medium)**: 1080p @ 60 FPS (RTX 3060+)
- **Console**: 4K @ 60 FPS / 1440p @ 120 FPS

## Controls

- **W / Arrow Up**: Throttle
- **S / Arrow Down**: Brake
- **A / Arrow Left**: Steer Left
- **D / Arrow Right**: Steer Right
- **Space**: Handbrake
- **Shift**: Nitro Boost
- **C**: Change Camera
- **ESC**: Pause/Menu
- **R**: Reset Vehicle

## Development Roadmap

### Phase 1 (Current)
- [x] Core engine architecture
- [x] Vehicle physics system
- [x] Basic renderer
- [ ] Terrain generation
- [ ] Weather system

### Phase 2
- [ ] Advanced graphics (ray tracing)
- [ ] Multiplayer infrastructure
- [ ] Voice chat integration
- [ ] Customization system

### Phase 3
- [ ] Console ports
- [ ] Online services
- [ ] Community features
- [ ] Monetization system

## Contributing

Contributions welcome! Please ensure:
1. Code follows C++20 style guidelines
2. All systems are properly documented
3. Performance impact is minimal
4. Tests pass on all platforms

## License

MIT License - See LICENSE file for details

## Credits

Developed by spidyninja928-web

Inspired by:
- Forza Horizon series
- Gran Turismo series
- Need for Speed series
