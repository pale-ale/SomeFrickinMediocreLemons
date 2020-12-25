#pragma once

#include <functional>
#include <map>
#include <string>
#include <vector>
#include <algorithm>
#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;

class Delegate{
    public:
    void ExecuteIfBound();
    void Bind(function<void()> * function);
    bool operator==(Delegate o);
    private:
    function<void()> * boundFunction;
};

class KeyboardDelegateManager{
    private:
    map<sf::Keyboard::Key, vector<Delegate>> bindings;
    vector<sf::Keyboard::Key> activeKeys;
    public:
    void SetupDelegateKeyBinding(Delegate delegate, sf::Keyboard::Key key);
    void RemoveBinding();
    void Tick();
};