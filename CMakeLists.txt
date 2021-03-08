cmake_minimum_required(VERSION 3.10)

project(SomeFrickinMediocreLemons LANGUAGES CXX)
#enable_testing()

# Force compiler to run in C++17 mode
set(CMAKE_CXX_STANDARD 17)

include_directories(UI PRIVATE {$YOUR_DIRECTORY})

# Create executable programs

# headers for UI
set(HEADER_FILES UI/UISystem.h   UI/Button.h   UI/PlayerHUD.h   UI/Bar.h   UI/CardSelector.h   UI/ManaBars.h UI/CardPreview.h)
add_library(UI   UI/UISystem.cpp UI/Button.cpp UI/PlayerHUD.cpp UI/Bar.cpp UI/CardSelector.cpp UI/ManaBars.cpp ${HEADER_FILES})

# headers for Delegates
set(HEADER_FILES KeyboardDelegate.h)
add_library(Delegate KeyboardDelegate.cpp ${HEADER_FILES})

# headers for specific cards
set(HEADER_FILES  card.h   cards/Fireball.h   cards/Kalle.h   cards/Vinesnatcher.h)
add_library(Cards card.cpp cards/Fireball.cpp cards/Kalle.cpp cards/Vinesnatcher.cpp ${HEADER_FILES})

# headers for Player, Game, CardType, ManaType, Battlefield, Scenes
set(HEADER_FILES Player.h   Game.h    Battlefield.h   Hand.h   Placeable.h   SceneManager.h   MainMenuScene.h cardTypes.h ManaType.h Scene.h)
add_library(Base Player.cpp Game.cpp  Battlefield.cpp Hand.cpp Placeable.cpp SceneManager.cpp MainMenuScene.cpp ${HEADER_FILES})
target_link_libraries(Base UI Cards)

add_executable(main main.cpp)
target_link_libraries(main UI Delegate Base Cards sfml-graphics sfml-window sfml-system)
