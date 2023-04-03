cmake_minimum_required(VERSION 3.0.0)

project(AimTraining)

set(CMAKE_CXX_STANDARD 17)

find_package(SFML 2.5 COMPONENTS graphics audio window network system REQUIRED)

add_executable(AimTraining main.cpp Game.cpp Game.h)

target_link_libraries(AimTraining sfml-graphics sfml-audio sfml-window sfml-network sfml-system)