#include <SFML/Graphics.hpp>
#include <vector>
#include <list>

using namespace std;

class UISystem : sf::Drawable{
    public:
    void processUIEvents(vector<sf::Event> events);
    void addChild(UIElement* newChild);
    void removeChild(UIElement* child);
    const list<UIElement*>* getChildren(){return children;}

    private:
    list<UIElement*>* children;
    bool isCoordInBounds(sf::Vector2f coords, const UIElement& element) const;
};

class UIElement : sf::Drawable{
    public:
    virtual void OnMouseButtonDown(sf::Event);
    virtual void OnMouseButtonUp(sf::Event);
    sf::Vector2f position;
    sf::Vector2f size;
    virtual void draw(sf::RenderTarget& target, sf::RenderStates state) const override{

    }

    public:
    const sf::Vector2f getBottomRight() const{return position+size;}
};