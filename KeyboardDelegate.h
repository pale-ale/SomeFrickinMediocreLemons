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
    void ExecuteIfBound(sf::Event);
    void ExecuteIfBound();
    void Bind(function<void(sf::Event)>* function);
    void Bind(function<void()>* function);
    private:
    function<void(sf::Event)> * boundEventFunction;
    function<void()> * boundFunction;
};

class KeyboardDelegateManager{
    private:
    map<sf::Keyboard::Key, vector<Delegate>> bindings;
    vector<sf::Event> keyEvents;
    public:
    void SetupDelegateKeyBinding(Delegate delegate, sf::Keyboard::Key key);
    void RemoveBinding();
    void Tick(vector<sf::Event> events);
};