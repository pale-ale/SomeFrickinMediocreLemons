cmake_minimum_required(VERSION 3.10)

project(SomeFrickinMediocreLemons LANGUAGES CXX)
#enable_testing()

# Force compiler to run in C++14 mode
set(CMAKE_CXX_STANDARD 14)

include_directories(UI PRIVATE {$YOUR_DIRECTORY})

# Create executable programs

# headers for Card, Player, Game, CardType, ManaType
set(HEADER_FILES card.h UI/Button.h cardTypes.h Game.h ManaType.h Player.h)
add_library(Base card.cpp UI/Button.cpp Game.cpp Player.cpp ${HEADER_FILES})

# headers for UI
set(HEADER_FILES UI/UISystem.h UI/Button.h)
add_library(UI UI/UISystem.cpp UI/Button.cpp ${HEADER_FILES})

# headers for Delegates
set(HEADER_FILES KeyboardDelegate.h)
add_library(Delegate KeyboardDelegate.cpp ${HEADER_FILES})

# headers for specific cards
set(HEADER_FILES cards/fireball.h)
add_library(Cards cards/fireball.cpp ${HEADER_FILES})


add_executable(main main.cpp)
target_link_libraries(main UI Delegate Base Cards sfml-graphics sfml-window sfml-system)
