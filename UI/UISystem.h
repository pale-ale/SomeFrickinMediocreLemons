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
    UIElement(UISystem *ui) : ui{ui} {};

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
    UISystem *ui = nullptr;
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
    list<UIElement *> hudElements = {};
    void addListener(UIElement *newListener);
    void addToHUD(UIElement* hudElement);
    void removeListener(UIElement *removeListener);
    bool isElementIn(const UIElement *e, const list<UIElement *> &l)
    {
        return std::find(l.begin(), l.end(), e) != l.end();
    }

    template <class T>
    UIElement *spawnNew();

private:
    sf::RenderWindow *window;
    bool isCoordInBounds(const sf::Vector2f &coords, const UIElement &element) const;
    sf::Vector2f getClosestPoint(const sf::Vector2f &point, const vector<sf::Vector2f> &points, int &index) const;
    float getDistance(const sf::Vector2f p1, const sf::Vector2f p2) const;
    list<UIElement *> getListenersUnderCoords(const sf::Vector2f &coords) const;

protected:
    virtual void draw(sf::RenderTarget &target, sf::RenderStates state) const override
    {
        UIElement::draw(target, state);
        for (auto &e : hudElements){
            target.draw(*e);
        }
    }
};