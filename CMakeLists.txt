cmake_minimum_required(VERSION 3.10)

project(SomeFrickinMediocreLemons LANGUAGES CXX)
#enable_testing()

# Force compiler to run in C++17 mode
set(CMAKE_CXX_STANDARD 17)

include_directories(UI PRIVATE {$YOUR_DIRECTORY})

# Create executable programs

# headers for UI
set(HEADER_FILES UI/UISystem.h   UI/Button.h   UI/PlayerHUD.h UI/Bars.h)
add_library(UI   UI/UISystem.cpp UI/Button.cpp UI/PlayerHUD.cpp UI/Bars.cpp ${HEADER_FILES})

# headers for Delegates
set(HEADER_FILES KeyboardDelegate.h)
add_library(Delegate KeyboardDelegate.cpp ${HEADER_FILES})

# headers for specific cards
set(HEADER_FILES cards/Fireball.h cards/Kalle.h)
add_library(Cards cards/Fireball.cpp cards/Kalle.cpp ${HEADER_FILES})

# headers for Card, Player, Game, CardType, ManaType, Battlefield, HUD
set(HEADER_FILES card.h Player.h UI/Button.h Game.h cardTypes.h ManaType.h Battlefield.h Hand.h Placeable.h UI/PlayerHUD.h UI/Bars.h)
add_library(Base card.cpp UI/Button.cpp Game.cpp Player.cpp Battlefield.cpp Hand.cpp Placeable.cpp UI/Bars.cpp ${HEADER_FILES})

add_executable(main main.cpp)
target_link_libraries(main UI Delegate Base Cards sfml-graphics sfml-window sfml-system)
