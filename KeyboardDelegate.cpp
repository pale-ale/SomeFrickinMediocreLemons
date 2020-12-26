#include "KeyboardDelegate.h"

void Delegate::Bind(function<void(sf::Event)>* function){
    boundFunction = function;
}

void Delegate::ExecuteIfBound(sf::Event event){
    (*boundFunction)(event);
}

void KeyboardDelegateManager::SetupDelegateKeyBinding(Delegate delegate, sf::Keyboard::Key key){
    auto functionBindings = &bindings[key];
    functionBindings->push_back(delegate);
}

void KeyboardDelegateManager::Tick(vector<sf::Event> events){
    for (int i=0; i<events.size(); i++){
        if (events[i].type == sf::Event::KeyPressed || events[i].type == sf::Event::KeyReleased){
            keyEvents.push_back(events[i]);
        }
    }
    for (int i=0; i<keyEvents.size(); i++){
        auto functions = bindings[keyEvents[i].key.code];
        for (int j=0; j<functions.size(); j++){
            functions[j].ExecuteIfBound(keyEvents[i]);
        }
    }
    keyEvents.clear();
}

void RemoveBinding(){};
