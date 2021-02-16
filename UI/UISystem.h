#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <list>
#include <iostream>
#include "../Placeable.h"
#include <algorithm>

using namespace std;

class UISystem;

class UIElement : public Placeable
{
protected:
    UIElement() = delete;
    UIElement(UISystem *ui):ui{ui}{};

public:
    virtual bool OnMouseButtonDown() { return false; }
    virtual bool OnMouseButtonUp() { return false; }
    virtual bool OnBeginMouseover()
    {
        cout << "Mouseover\n";
        return false;
    }
    virtual bool OnEndMouseover()
    {
        cout << "Mouseout\n";
        return false;
    }
    UISystem* ui = nullptr;
    bool isDragable;
    bool isMouseovering;
    bool isVisible = true;

    virtual void draw(sf::RenderTarget &target, sf::RenderStates state) const override;
};

class UISystem : public UIElement
{
public:
    UISystem(sf::RenderWindow *inWindow) : UIElement(nullptr)
    {
        window = inWindow;
    };
    void processEvents(vector<sf::Event> events);
    list<UIElement *> eventListeners = {};
    list<UIElement *> mouseOveredListeners = {};
    void addListener(UIElement *newListener);
    bool isElementIn(const UIElement *e, const list<UIElement *> &l)
    {
        return std::find(l.begin(), l.end(), e) != l.end();
    }

    template<class T>
    UIElement *spawnNew();


private:
    sf::RenderWindow *window;
    bool isCoordInBounds(const sf::Vector2f &coords, const UIElement &element) const;
    list<UIElement *> getListenersUnderCoords(const sf::Vector2f &coords) const;
};