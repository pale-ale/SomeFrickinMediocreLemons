#pragma once

#include <algorithm>
#include <iostream>
#include <list>
#include "../Placeable.h"
#include "UIElement.h"
#include <SFML/Graphics.hpp>
#include <vector>

using namespace std;

class UISystem : public UIElement
{
public:
    UISystem(sf::RenderWindow *inWindow) : UIElement(nullptr)
    {
        window = inWindow;
    };
    void processEvents(vector<sf::Event> events);
    list<weak_ptr<UIElement>> eventListeners = {};
    list<weak_ptr<UIElement>> mouseOveredListeners = {};
    weak_ptr<UIElement> currentlyInteractingElement;
    bool bWasInteractingElementDragged = false;
    list<shared_ptr<UIElement>> hudElements = {};
    void addEventListener(weak_ptr<UIElement> newListener);
    void addToHUDLayer(shared_ptr<UIElement> hudElement);
    void removeFromHUDLayer(UIElement *hudElement);
    void removeEventListener(UIElement *listener);
    void handleMouseDownEvent(const sf::Event &mouseDownEvent);
    void handleMouseUpEvent(const sf::Event &mouseUpEvent);
    void handleMouseMoveEvent(const sf::Event &mouseMoveEvent);
    bool isPtrIn(const weak_ptr<UIElement> e, const list<weak_ptr<UIElement>> &l)
    {
        for (auto x : l){
            if (x.lock() == e.lock() && x.lock())
                return true;
        }
        return false;
    }
    bool removePtr(const weak_ptr<UIElement> e, list<weak_ptr<UIElement>> &l)
    {
        auto start = l.begin();
        auto end = l.end();
        auto cmp = e.lock();
        while (start != end){
            if (start->lock() == cmp){
                l.erase(start);
                return true;
            }
            ++start;
        }
        return false;
    }
    bool removePtr(const UIElement *e, list<shared_ptr<UIElement>> &l){
        auto start = l.begin();
        auto end = l.end();
        while (start != end){
            if (start->get() == e){
                l.erase(start);
                return true;
            }
            ++start;
        }
        return false;
    }

private:
    sf::RenderWindow *window;
    bool isCoordInBounds(const sf::Vector2f &coords, const UIElement *element) const;
    sf::Vector2f getClosestPoint(const sf::Vector2f &point, const vector<sf::Vector2f> &points, int &index) const;
    float getDistance(const sf::Vector2f &p1, const sf::Vector2f &p2) const;
    list<weak_ptr<UIElement>> getListenersUnderCoords(const sf::Vector2f &coords) const;

protected:
    virtual void draw(sf::RenderTarget &target, sf::RenderStates state) const override
    {
        UIElement::draw(target, state);
        for (auto &e : hudElements){
            target.draw(*e);
        }
    }
};