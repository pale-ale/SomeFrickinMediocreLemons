#include "Button.h"

Button::Button(sf::Rect<float> rect){
    this->rect = rect;
    size = sf::Vector2f(rect.width, rect.height);
    buttonShape = sf::RectangleShape({rect.width, rect.height});
    buttonShape.setFillColor(sf::Color(255, 0, 255, 100));
    buttonShape.setOrigin(size/2.0f);
    position = sf::Vector2f(rect.left, rect.top);
    callback = new EventCallback<Button>(this, &Button::OnMouseButtonDown);
    buttonTexture = sf::Texture();
}

void Button::SetPosition(sf::Vector2f newPosition){
    position = newPosition;
    buttonShape.setPosition(position);
}

void Button::SetRotation(float newRotation){
    buttonShape.setRotation(newRotation);
}