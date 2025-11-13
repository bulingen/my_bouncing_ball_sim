cmake_minimum_required(VERSION 3.10)
project(BouncingBallSim)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find Stonefish package
find_package(Stonefish REQUIRED)

# Add executable
add_executable(bouncing_ball
    main.cpp
    MySimulationManager.cpp
    MySimulationApp.cpp
)

# Link against Stonefish (includes headers automatically)
target_link_libraries(bouncing_ball
    Stonefish::Stonefish
)