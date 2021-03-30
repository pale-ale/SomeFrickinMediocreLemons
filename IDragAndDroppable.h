#include <SFML/Graphics.hpp>
#include <vector>

using std::vector;

class IDragAndDroppable{
    public:
    virtual void OnDragStart() = 0;
    virtual void OnDragEnd() = 0;
    virtual void OnDragMove(const sf::Vector2f &pos) = 0;
    virtual void setSnapPoints(const vector<sf::Vector2f> &points) = 0;
};
