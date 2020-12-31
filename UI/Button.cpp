#include "Button.h"

Button::Button(sf::Rect<float> rect){
    this->rect = rect;
    this->buttonTexture = sf::Texture();
    buttonShape = sf::RectangleShape({rect.width, rect.height});
    buttonShape.setFillColor(sf::Color(255, 0, 255, 100));
    this->position = sf::Vector2f(rect.left, rect.top);
    this->size = sf::Vector2f(rect.width, rect.height);
    callback = new EventCallback<Button>(this, &Button::OnMouseButtonDown);
}

void Button::SetPosition(sf::Vector2f newPosition){
    position = newPosition;
    buttonShape.setPosition(position);
}
