cmake_minimum_required(VERSION 3.25)
project(ARKANOID_THE_GAME)
add_executable(ARKANOID_THE_GAME main.cpp Statistics.h Ball.cpp Ball.h Bogey.cpp Bogey.h Block.cpp Block.h Bonus.cpp Bonus.h Options.h Rectangle.cpp Rectangle.h Collisions.h Collisions.cpp Game.cpp Game.h)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(SFML_STATIC_LIBRARIES TRUE)
set(SFML_DIR C:/SFML/lib/cmake/SFML)

find_package(SFML COMPONENTS system window graphics audio network REQUIRED)

include_directories(C:/SFML/include)
target_link_libraries(ARKANOID_THE_GAME sfml-system sfml-window sfml-graphics sfml-audio)
