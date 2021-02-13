#include "UISystem.h"

bool UISystem::isCoordInBounds(const sf::Vector2f &coords, const UIElement &element) const
{
    auto tl = element.getPosition() - element.getSize() / 2.0f;
    auto br = element.getBottomRight();
    return tl.x <= coords.x && tl.y <= coords.y &&
           br.x >= coords.x && br.y >= coords.y;
}

list<UIElement *> UISystem::getListenersUnderCoords(const sf::Vector2f &coords) const
{
    list<UIElement *> listeners;
    auto eventListener_it = eventListeners.rbegin();
    while (eventListener_it != eventListeners.rend())
    {
        auto listener = *eventListener_it;
        auto mouseCoords = window->mapPixelToCoords(sf::Mouse::getPosition(*window));
        if (isCoordInBounds(mouseCoords, *listener))
        {
            listeners.push_back(listener);
        }
        eventListener_it++;
    }
    return listeners;
}

void UISystem::addListener(UIElement *newListener)
{
    for (UIElement *listener : eventListeners)
    {
        if (listener == newListener)
        {
            cout << "listener already added!\n";
            throw;
        }
    }
    eventListeners.push_back(newListener);
}

void UISystem::processEvents(vector<sf::Event> events)
{
    auto event_it = events.begin();
    while (event_it != events.end())
    {
        auto event = *event_it;
        switch (event.type)
        {
        case sf::Event::MouseButtonPressed:
        {
            auto mouseCoords = window->mapPixelToCoords(sf::Mouse::getPosition(*window));
            for (auto l : getListenersUnderCoords(mouseCoords))
            {
                if (l->isVisible && l->OnMouseButtonDown())
                {
                    break;
                }
            }
            break;
        }
        case sf::Event::MouseMoved:
        {
            //cout << event.mouseMove.x << " | " << event.mouseMove.y << endl;
            auto mouseCoords = window->mapPixelToCoords(sf::Mouse::getPosition(*window));
            auto currentMOElements = getListenersUnderCoords(mouseCoords);
            list<UIElement*> newListeners = {};
            for (auto l_it = mouseOveredListeners.begin(); l_it != mouseOveredListeners.end(); l_it++)
            {
                //is the listener part of the currently mouseovered ones?
                if (!isElementIn(*l_it, currentMOElements))
                {
                    //if not, the listener is not being mouseovered anymore
                    (*l_it)->OnEndMouseover();
                    mouseOveredListeners.erase(l_it--);
                }
                //remove the listener from the input queue aswell for performance (maybe?)
                currentMOElements.remove(*l_it);
            }
            for (auto listener : currentMOElements){
                if (!isElementIn(listener, mouseOveredListeners))
                {
                    //if the listener is new
                    mouseOveredListeners.push_back(listener);
                    listener->OnBeginMouseover();
                }
            }
            break;
        }
        default:
            break;
        }
        event_it++;
    }
}

void UIElement::draw(sf::RenderTarget &target, sf::RenderStates state) const
{
    auto child_it = children.begin();
    while (child_it != children.end())
    {
        target.draw(**child_it);
        child_it++;
    }
};
