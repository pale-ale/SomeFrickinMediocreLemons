#include <SFML/Graphics.hpp>
#include <math.h>

inline static float getDistance(const sf::Vector2f &a, const sf::Vector2f &b){
    return sqrt(pow(a.x-b.x, 2) + pow(a.y-b.y, 2));
}

template <typename T>
inline static sf::Vector2f getClosestPoint(const sf::Vector2f &a, const T &b){
    if(b.size() < 1){
        throw;
    }
    float d = getDistance(a, b[0]);
    sf::Vector2f closest = b[0];
    for (const sf::Vector2f &point : b){
        float newDist = getDistance(a, point);
        if(newDist < d){
            d = newDist;
            closest = point;
        }
    }
    return closest;
}
