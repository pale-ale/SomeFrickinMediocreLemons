cmake_minimum_required(VERSION 3.10)

project(SomeFrickinMediocreLemons LANGUAGES CXX)
#enable_testing()

# Force compiler to run in C++17 mode
set(CMAKE_CXX_STANDARD 17)

include_directories(UI PRIVATE {$YOUR_DIRECTORY})

# Create executable programs

# headers for UI
set(HEADER_FILES    ui/UISystem.h   ui/UIElement.h     ui/ActionSelector.h   
ui/Button.h     ui/PlayerHUD.h     ui/Bar.h 
ui/CardSelector.h   ui/ManaBars.h   ui/CardPreview.h   ui/QuickTextBox.h 
ui/TextBox.h)

add_library(UI      ui/UISystem.cpp ui/UIElement.cpp   ui/ActionSelector.cpp 
ui/Button.cpp   ui/PlayerHUD.cpp   ui/Bar.cpp
ui/CardSelector.cpp ui/ManaBars.cpp ui/CardPreview.cpp ui/QuickTextBox.cpp
ui/TextBox.cpp ${HEADER_FILES})

# headers for Delegates
set(HEADER_FILES KeyboardDelegate.h)
add_library(Delegate KeyboardDelegate.cpp ${HEADER_FILES})

# headers for specific cards
set(HEADER_FILES  Card.h   cards/Fireball.h   cards/Kalle.h   cards/Vinesnatcher.h   cards/PlayerCard.h)
add_library(Cards Card.cpp cards/Fireball.cpp cards/Kalle.cpp cards/Vinesnatcher.cpp cards/PlayerCard.cpp ${HEADER_FILES})

# headers for actions
set(HEADER_FILES  IAction.h actions/DefaultAttack.h   actions/VinesnatcherTap.h   actions/FireballTap.h)
add_library(Actions         actions/DefaultAttack.cpp actions/VinesnatcherTap.cpp actions/FireballTap.cpp ${HEADER_FILES})

# headers for Player, Game, CardType, ManaType, Battlefield, Scenes
set(HEADER_FILES Player.h          Game.h    Battlefield.h   Hand.h   Placeable.h   SceneManager.h   
                 MainMenuScene.h   GameScene.h   CardManagement.h ManaType.h Scene.h)
add_library(Base Player.cpp        Game.cpp  Battlefield.cpp Hand.cpp Placeable.cpp SceneManager.cpp 
                 MainMenuScene.cpp GameScene.cpp CardManagement.cpp ${HEADER_FILES})
target_link_libraries(Base UI Cards)

add_executable(main main.cpp)
target_link_libraries(main UI Delegate Base Cards Actions sfml-graphics sfml-window sfml-system)
