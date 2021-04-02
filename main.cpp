#include "events/EventCallback.h"
#include "GameScene.h"
#include <iostream>
#include "KeyboardDelegate.h"
#include "MainMenuScene.h"
#include "math.h"
#include "Scene.h"
#include "SceneManager.h"
#include "Settings.h"
#include <SFML/Graphics.hpp>
#include <string.h>
#include "ui/UISystem.h"
#include <vector>

int main(int argc, char *argv[])
{
    string progRelativepath(argv[0]);
    // cut off everything after the last "/", leaving us with the current directory
    string dirRelativePath(progRelativepath.substr(0, progRelativepath.find_last_of("/")) + "/../");
    Settings::programDir = dirRelativePath.c_str();
    sf::RenderWindow window(sf::VideoMode(Settings::defaultWidth, Settings::defaultHeight), 
        "Card Game",
        sf::Style::Default
        );

    // IMPORTANT: These will be destroyed in reverse order (bottom to top), so you better not
    // put the sceneManager after the UI (cleanup will crash due to buttons not being able to unlisten)!
    KeyboardDelegateManager delegateHandler;
    UISystem ui(&window);
    Delegate spaceDelegate;
    SceneManager sceneManager;

    float scale = 2;
    window.setKeyRepeatEnabled(false);
    window.setSize({(uint)(Settings::defaultWidth*scale), (uint)(Settings::defaultHeight*scale)});
    window.setVerticalSyncEnabled(true);

    auto testFont = sf::Font();
    for (const char* testPath : Settings::defaultFontPaths){
        if(testFont.loadFromFile(testPath)){
            Settings::validFontPath = testPath;
            break;
        }
    }
    if (!Settings::validFontPath){
        cout << "No valid fontpath found. Take a look at Settings.h and change the paths accordingly.\n";
        throw;
    }
    
    vector<sf::Event> events;
    sf::Clock clock;
    
    auto ms = std::make_unique<MainMenuScene>(&ui, sceneManager);
    auto gs = std::make_unique<GameScene>(&ui, sceneManager);
    ms->setGameScene(std::move(gs));
    sceneManager.loadScene(std::move(ms));
    while (window.isOpen())
    {
        sf::Time tickDelay = clock.getElapsedTime();
        clock.restart();
        
        sf::Event event;
        while (window.pollEvent(event))
        {
            events.push_back(event);
            if (event.type == sf::Event::Closed)
                window.close();
        }
        delegateHandler.Tick(events);
        ui.processEvents(events);
        events.clear();
        window.clear();
        auto s = sceneManager.getScene();
        s->tick(tickDelay.asMilliseconds());
        window.draw(*s);
        window.draw(ui);
        window.display();
    }
    return 0;
}
