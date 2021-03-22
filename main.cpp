#include "Events/EventCallback.h"
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
#include "UI/UISystem.h"
#include <vector>

using std::cout;
using std::endl;

int main()
{
    sf::RenderWindow window(sf::VideoMode(
        Settings::defaultWidth, 
        Settings::defaultHeight), 
        "Nothing works!!",
        sf::Style::Default
        );
    KeyboardDelegateManager delegateHandler;
    Delegate spaceDelegate;
    SceneManager sceneManager;
    UISystem ui(&window);
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
        cout << "No valid fontpath found.\n";
        throw;
    }
    
    vector<sf::Event> events;
    sf::Clock clock;

    MainMenuScene *ms = new MainMenuScene(&ui, sceneManager);
    auto gs = new GameScene(&ui, sceneManager);
    ms->setGameScene(gs);
    sceneManager.loadScene(ms);

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
