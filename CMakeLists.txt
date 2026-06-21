cmake_minimum_required(VERSION 3.20)
project(OpenHorizonEngine VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -march=native -flto")

# Engine core
add_library(openHorizonCore
    src/engine/core/Engine.cpp
    src/engine/core/Window.cpp
    src/engine/core/Clock.cpp
    src/engine/rendering/Renderer.cpp
    src/engine/rendering/Camera.cpp
    src/engine/physics/PhysicsEngine.cpp
    src/engine/physics/Vehicle.cpp
    src/engine/world/Terrain.cpp
    src/engine/world/World.cpp
    src/engine/input/InputManager.cpp
    src/engine/audio/AudioEngine.cpp
    src/game/GameState.cpp
    src/game/RaceManager.cpp
)

target_include_directories(openHorizonCore PUBLIC include)

# Dependencies
find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)
find_package(glm REQUIRED)
find_package(Bullet REQUIRED)
find_package(OpenAL REQUIRED)

target_link_libraries(openHorizonCore
    OpenGL::OpenGL
    glfw
    glm::glm
    ${BULLET_LIBRARIES}
    OpenAL::OpenAL
)

# Main executable
add_executable(OpenHorizon src/main.cpp)
target_link_libraries(OpenHorizon openHorizonCore)
