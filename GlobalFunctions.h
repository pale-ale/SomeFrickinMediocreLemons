#pragma once

#include <SFML/Graphics.hpp>
#include <math.h>

inline static float getDistance(const sf::Vector2f &a, const sf::Vector2f &b){
    return sqrt(pow(a.x-b.x, 2) + pow(a.y-b.y, 2));
}

template <typename T>
inline static sf::Vector2f getClosestPoint(const sf::Vector2f &a, const T &b, int &inIndex = -1){
    if(b.size() < 1){
        throw;
    }
    inIndex = 0;
    float smallestDistance = getDistance(a, b[inIndex]);
    for (int i=0; i<b.size(); ++i){
        float tmpDistance = getDistance(a, b[i]);
        if (tmpDistance < smallestDistance){
            inIndex = i;
            smallestDistance = tmpDistance;
        }
    }
    return b[inIndex];
}
