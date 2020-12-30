#include "Button.h"

Button::Button(sf::Rect<float> rect){
    this->rect = rect;
    this->buttonTexture = sf::Texture();
    buttonShape = sf::RectangleShape({rect.width, rect.height});
    buttonShape.setFillColor(sf::Color::Magenta);
    this->position = sf::Vector2f(rect.left, rect.top);
    this->size = sf::Vector2f(rect.width, rect.height);
}