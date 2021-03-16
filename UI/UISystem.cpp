#include "UISystem.h"
#include "math.h"

bool UISystem::isCoordInBounds(const sf::Vector2f &coords, const UIElement &element) const
{
    auto& hb = element.getHitboxPolygonGlobal();
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

    auto tl = element.getPosition() - element.getSize() / 2.0f;
    auto br = element.getBottomRight();
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

void UISystem::removeListener(UIElement *removeListener)
{
    eventListeners.remove(removeListener);
    mouseOveredListeners.remove(removeListener);
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
                if (l->isVisible && l->OnMouseButtonDown())
                {
                    break;
                }
            }
            break;
        }
        case sf::Event::MouseButtonReleased:
        {
            auto mouseCoords = window->mapPixelToCoords(sf::Mouse::getPosition(*window));
            for (auto l : getListenersUnderCoords(mouseCoords))
            {
                if (l->isVisible && l->OnMouseButtonUp())
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

template<class T>
UIElement* UISystem::spawnNew()
{
    if (ui)
    {
        return ui->spawnNew<T>();
    }
    cout << "Dead end of parent chain?\n";
    return nullptr;
};

void UIElement::draw(sf::RenderTarget &target, sf::RenderStates state) const
{
    Placeable::draw(target, state);
};
