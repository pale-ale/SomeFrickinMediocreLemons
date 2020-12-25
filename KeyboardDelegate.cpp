#include "KeyboardDelegate.h"

void Delegate::Bind(function<void()>* function){
    boundFunction = function;
}

void Delegate::ExecuteIfBound(){
    (*boundFunction)();
}

bool Delegate::operator==(Delegate o){
    return o.boundFunction == boundFunction;
}

void KeyboardDelegateManager::SetupDelegateKeyBinding(Delegate delegate, sf::Keyboard::Key key){
    auto functionBindings = &bindings[key];
    if(find(functionBindings->begin(), functionBindings->end(), delegate) == functionBindings->end()){
        functionBindings->push_back(delegate);
    }else{
        throw "Binding with same function and keycombo already exists.";
    }
    
}

void KeyboardDelegateManager::Tick(){
    for (int i=0; i<sf::Keyboard::KeyCount; i++){
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(i))){
            activeKeys.push_back(sf::Keyboard::Key(i));
        }
    }
    // we wouldnt want a keystroke to get lost because of a long tick of a delegate, so we save it's state in activekeys[]
    for (int i=0; i<activeKeys.size(); i++){
        auto functions = bindings[activeKeys[i]];
        for (int j=0; j<functions.size(); j++){
            functions[j].ExecuteIfBound();
        }
    }
    activeKeys.clear();
}

void RemoveBinding(){};
