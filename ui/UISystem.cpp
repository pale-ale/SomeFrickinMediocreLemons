#include "UISystem.h"
#include "math.h"

bool UISystem::isCoordInBounds(const sf::Vector2f &coords, const UIElement *element) const
{
    auto &hb = element->getHitboxPolygonGlobal();
    if (hb.size() < 3)
    {
        return false;
    }
    int index;
    auto pos = getClosestPoint(coords, hb, index);
    sf::Vector2f a = hb[(index + 1) % hb.size()] - pos;
    sf::Vector2f b = hb[(index - 1) % hb.size()] - pos;
    sf::Vector2f n = coords - pos;
    int axn = a.x * n.y - a.y * n.x;
    int nxb = n.x * b.y - n.y * b.x;
    return axn >= 0 && nxb >= 0;
}

sf::Vector2f UISystem::getClosestPoint(const sf::Vector2f &point, const vector<sf::Vector2f> &points, int &index) const
{
    if (points.size() < 3)
    {
        cout << "UISystem: less than 3 points aint no polygon!\n";
        throw;
    }
    float minDist = getDistance(point, points[0]);
    index = 0;
    for (int i = 0; i < points.size(); i++)
    {
        float d = getDistance(point, points[i]);
        if (d < minDist)
        {
            minDist = d;
            index = i;
        }
    }
    return points[index];
}

float UISystem::getDistance(const sf::Vector2f &p1, const sf::Vector2f &p2) const
{
    return sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2));
}

list<weak_ptr<UIElement>> UISystem::getListenersUnderCoords(const sf::Vector2f &coords) const
{
    list<weak_ptr<UIElement>> listeners;
    auto eventListener_it = eventListeners.rbegin();
    while (eventListener_it != eventListeners.rend())
    {
        auto mouseCoords = window->mapPixelToCoords(sf::Mouse::getPosition(*window));
        if (isCoordInBounds(mouseCoords, eventListener_it->lock().get()))
        {
            listeners.push_back(*eventListener_it);
        }
        eventListener_it++;
    }
    return listeners;
}

void UISystem::addListener(weak_ptr<UIElement> newListener)
{
    auto listenerSharedptr = static_pointer_cast<UIElement>(newListener.lock());
    if (!listenerSharedptr)
    {
        cout << "UISystem: tried to add bad listener. Maybe null or not a UIElement?\n";
        throw;
    }
    cout << "UISystem: Adding weak Listener at " << listenerSharedptr.get() << endl;
    for (auto listener : eventListeners)
    {
        if (listener.lock().get() == listenerSharedptr.get())
        {
            cout << "UISystem: Listener already added!\n";
            throw;
        }
    }
    eventListeners.push_back(listenerSharedptr);
}

void UISystem::removeListener(UIElement *listener)
{
    cout << "UISystem: Removing listener at: " << listener << (listener ? (" named '" + listener->getName() + "'\n") : "\n");
    auto start = eventListeners.begin();
    auto end = eventListeners.end();
    auto ciePtr = currentlyInteractingElement.lock();
    if (ciePtr.get() == listener)
    {
        cout << "UISystem: Aborting interaction on this listener.\n";
        ciePtr.reset();
    }
    while (start != end)
    {
        auto l = start->lock().get();
        if (l == listener || !l)
        {
            removeWeakPtr(*start, mouseOveredListeners);
            eventListeners.erase(start);
            return;
        }
        start++;
    }
    cout << "UISystem: Tried to remove listener that isn't registered.\n";
    throw;
}

void UISystem::addToHUD(UIElement *hudElement)
{
    hudElements.push_back(hudElement);
}

void UISystem::handleMouseDownEvent(const sf::Event &mouseDownEvent)
{
    const auto mouseCoords = window->mapPixelToCoords(sf::Mouse::getPosition(*window));
    const auto listeners = getListenersUnderCoords(mouseCoords);
    for (auto l : listeners)
    {
        auto lPtr = l.lock();
        if (!lPtr)
        {
            // not yet sure if this is actually an error one sohuld care about if a button is destroyed 
            // when considered for an event...
            //cout << "UISystem: Got invalid UIElement under Cursor.\n";
            //throw;
            return;
        }
        if (lPtr->isVisible && lPtr->OnMouseButtonDown())
        {
            currentlyInteractingElement = l;
        }
    }
}

void UISystem::handleMouseUpEvent(const sf::Event &mouseUpEvent)
{
    auto mouseCoords = window->mapPixelToCoords(sf::Mouse::getPosition(*window));
    auto interactingElement = currentlyInteractingElement.lock();
    if (interactingElement)
    {
        if (bWasInteractingElementDragged)
        {
            bWasInteractingElementDragged = false;
            interactingElement->OnDragEnd();
        }
        else
        {
            interactingElement->OnClick();
        }
        currentlyInteractingElement.reset();
    }
    for (auto l : getListenersUnderCoords(mouseCoords))
    {
        if (l.lock()->isVisible && l.lock()->OnMouseButtonUp())
        {
            return;
        }
    }
}

void UISystem::handleMouseMoveEvent(const sf::Event &event)
{
    auto mouseCoords = window->mapPixelToCoords(sf::Mouse::getPosition(*window));
    auto interactingElement = currentlyInteractingElement.lock();
    if (interactingElement && interactingElement->isDragable)
    {
        if (bWasInteractingElementDragged)
        {
            interactingElement->OnDragMove(mouseCoords);
        }
        else
        {
            interactingElement->OnDragStart();
            bWasInteractingElementDragged = true;
        }
        return;
    }
    auto currentMOElements = getListenersUnderCoords(mouseCoords);
    for (auto l_it = mouseOveredListeners.begin(); l_it != mouseOveredListeners.end(); l_it++)
    {
        //is the listener part of the currently mouseovered ones?
        if (!isWeakPtrIn(*l_it, currentMOElements))
        {
            auto lPtr = l_it->lock();
            //if not, the listener is not being mouseovered anymore
            if (lPtr)
            {
                lPtr->OnEndMouseover();
            }
            mouseOveredListeners.erase(l_it--);
        }
        //remove the listener from the input queue aswell for performance (maybe?)
        removeWeakPtr(*l_it, currentMOElements);
    }
    for (auto listener : currentMOElements)
    {
        if (!isWeakPtrIn(listener, mouseOveredListeners))
        {
            //if the listener is new
            mouseOveredListeners.push_back(listener);
            listener.lock()->OnBeginMouseover();
        }
    }
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
            handleMouseDownEvent(event);
            break;
        }
        case sf::Event::MouseButtonReleased:
        {
            handleMouseUpEvent(event);
            break;
        }
        case sf::Event::MouseMoved:
        {
            handleMouseMoveEvent(event);
            break;
        }
        default:
            break;
        }
        event_it++;
    }
}
