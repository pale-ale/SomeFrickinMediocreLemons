#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <list>
#include <iostream>
#include "../Placeable.h"
#include <algorithm>

using namespace std;

class UIElement : public Placeable{
    public:
    virtual bool OnMouseButtonDown(){return false;}
    virtual void OnMouseButtonUp(){}
    virtual void OnBeginMouseover(){cout << "Mouseover\n";}
    virtual void OnEndMouseover(){cout << "Mouseout\n";}
    bool isDragable;
    bool isMouseovering;
    bool isVisible = true;

    virtual void draw(sf::RenderTarget& target, sf::RenderStates state) const override;
};

class UISystem : public UIElement{
    public:
    UISystem(sf::RenderWindow* inWindow){window=inWindow;};
    void processEvents(vector<sf::Event> events);
    list<UIElement*> eventListeners = {};
    list<UIElement*> mouseOveredListeners = {};
    void addListener(UIElement* newListener);
    bool isElementIn(const UIElement* e, const list<UIElement*>& l){
        return std::find(l.begin(), l.end(), e) != l.end();
    }
   
    private:
    sf::RenderWindow* window;
    bool isCoordInBounds(const sf::Vector2f& coords, const UIElement& element) const;
    list<UIElement*> getListenersUnderCoords(const sf::Vector2f& coords) const;
};