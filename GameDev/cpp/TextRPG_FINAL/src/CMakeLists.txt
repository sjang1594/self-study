cmake_minimum_required(VERSION 3.23)
project(src)

set(CMAKE_CXX_STANDARD 14)

include_directories(Creature)
include_directories(Game)

add_executable(src
        Creature/Creature.cpp
        Creature/Creature.h
        Creature/Monster.cpp
        Creature/Monster.h
        Creature/Player.cpp
        Creature/Player.h
        Game/Field.cpp
        Game/Field.h
        Game/Game.cpp
        Game/Game.h
        main.cpp)
