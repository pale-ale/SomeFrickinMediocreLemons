#include "UISystem.h"
#include "math.h"

bool UISystem::isCoordInBounds(const sf::Vector2f &coords, const UIElement *element) const
{
    auto& hb = element->getHitboxPolygonGlobal();
    if (hb.size() < 3){
        return false;
    }
    int index;
    auto pos = getClosestPoint(coords, hb, index);
    sf::Vector2f a = hb[(index+1)%hb.size()] - pos;
    sf::Vector2f b = hb[(index-1)%hb.size()] - pos;
    sf::Vector2f n = coords - pos;
    int axn = a.x * n.y - a.y * n.x;
    int nxb = n.x * b.y - n.y * b.x;

    return axn > 0 && nxb > 0;

    auto tl = element->getPosition() - element->getSize() / 2.0f;
    auto br = element->getBottomRight();
    return tl.x <= coords.x && tl.y <= coords.y &&
           br.x >= coords.x && br.y >= coords.y;
}

sf::Vector2f UISystem::getClosestPoint(const sf::Vector2f &point, const vector<sf::Vector2f> &points, int &index) const
{
    if (points.size() < 3){
        cout << "UISystem: less than 3 points aint no polygon!\n";
        throw;
    }
    float minDist = getDistance(point, points[0]);
    index = 0;
    for (int i=0; i<points.size(); i++){
        float d = getDistance(point, points[i]);
        if (d < minDist){
            minDist = d;
            index = i;
        }
    }
    return points[index];
}

float UISystem::getDistance(const sf::Vector2f p1, const sf::Vector2f p2) const{
    return sqrt(pow(p1.x-p2.x, 2) + pow(p1.y - p2.y, 2));
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
    if (!listenerSharedptr){
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
    cout << "UISystem: Removing listener at: " << listener << endl;
    auto start = eventListeners.begin();
    auto end = eventListeners.end();
    while (start != end){
        auto l = start->lock().get();
        auto ccePtr = currentlyClickingElement.lock().get();
        auto cdePtr = currentlyDraggedElement.lock().get();
        if (l == listener || !l){
            cout << "UISystem: " << ccePtr << ", " << listener << endl;
            if (cdePtr == listener)
                cout << "UISystem: Aborting click on this listener.\n";
                currentlyDraggedElement.reset();
            if (ccePtr == listener){
                cout << "UISystem: Aborting click on this listener.\n";
                currentlyClickingElement.reset();
            }
            removeWeakPtr(*start, mouseOveredListeners);
            eventListeners.erase(start);
            return;
        }
        start++;
    }
    cout << "UISystem: Tried to remove listener that isn't registered.\n";
    throw;
}

void UISystem::addToHUD(UIElement* hudElement){
    hudElements.push_back(hudElement);
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
                auto lPtr = l.lock();
                if (!lPtr){
                    cout << "UISystem: Got invalid UIElement under Cursor.\n";
                    throw;
                }
                if (lPtr->isVisible && lPtr->OnMouseButtonDown())
                {
                    if (lPtr && lPtr->isDragable){
                        currentlyDraggedElement = l;
                    }
                    if (lPtr){
                        cout << "\n\ndraggyboi\n\n";
                        currentlyClickingElement = l;
                    }
                    break;
                }
            }
            break;
        }
        case sf::Event::MouseButtonReleased:
        {
            auto draggedElement = currentlyDraggedElement.lock();
            auto clickingElement = currentlyClickingElement.lock();
            auto mouseCoords = window->mapPixelToCoords(sf::Mouse::getPosition(*window));
            if (draggedElement && draggedElement->gotDragged){
                draggedElement->OnDragEnd();
                currentlyDraggedElement.reset();
                break;
            }
            if (clickingElement){
                cout << currentlyClickingElement.lock() << endl;
                clickingElement->OnClick();
                currentlyClickingElement.reset();
                break;
            }
            for (auto l : getListenersUnderCoords(mouseCoords))
            {
                if (l.lock()->isVisible && l.lock()->OnMouseButtonUp())
                {
                    break;
                }
            }
            break;
        }
        case sf::Event::MouseMoved:
        {
            auto mouseCoords = window->mapPixelToCoords(sf::Mouse::getPosition(*window));
            auto dragged = currentlyDraggedElement.lock();
            if (dragged){
                if (!dragged->gotDragged){
                    dragged->OnDragStart();
                }
                dragged->OnDragMove(mouseCoords);
                return;
            }
            auto currentMOElements = getListenersUnderCoords(mouseCoords);
            for (auto l_it = mouseOveredListeners.begin(); l_it != mouseOveredListeners.end(); l_it++)
            {
                //is the listener part of the currently mouseovered ones?
                if (!isWeakPtrIn(*l_it, currentMOElements))
                {
                    //if not, the listener is not being mouseovered anymore
                    l_it->lock()->OnEndMouseover();
                    mouseOveredListeners.erase(l_it--);
                }
                //remove the listener from the input queue aswell for performance (maybe?)
                removeWeakPtr(*l_it, currentMOElements);
            }
            for (auto listener : currentMOElements){
                if (!isWeakPtrIn(listener, mouseOveredListeners))
                {
                    //if the listener is new
                    mouseOveredListeners.push_back(listener);
                    listener.lock()->OnBeginMouseover();
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
    Placeable::draw(target, state);
};
