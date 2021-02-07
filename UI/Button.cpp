#include "Button.h"

Button::Button(sf::Rect<float> rect){
    this->rect = rect;
    size = sf::Vector2f(rect.width, rect.height);
    buttonShape = sf::RectangleShape({rect.width, rect.height});
    buttonShape.setFillColor(sf::Color(255, 0, 255, Settings::bEnableButtonTint ? 100 : 0));
    buttonShape.setOrigin(size/2.0f);
    transform.setPosition(sf::Vector2f(rect.left, rect.top));
    buttonTexture = sf::Texture();
}

void Button::setPosition(sf::Vector2f newPosition){
    transform.setPosition(newPosition);
    buttonShape.setPosition(newPosition);
}

void Button::setRotation(float newRotation){
    buttonShape.setRotation(newRotation);
}

bool Button::OnMouseButtonDown(){
    //we wouldnt want our click-callback to change the handlevent param before returning
    auto returnValue = handleEvent;
    if (callback){
        (*callback)();
    }else{
        cout << "Ignoring callback that isn't configured yet!";
    }
    return returnValue;
}