#include "Button.h"

Button::Button(UISystem* ui, sf::Rect<float> rect, sf::Color color):
UIElement(ui){
    size = sf::Vector2f(rect.width, rect.height);
    Placeable::setSize(size);
    this->rect = rect;
    buttonShape = sf::RectangleShape(size);
    buttonShape.setFillColor(color);
    buttonShape.setOrigin(size/2.0f);
    transform.setPosition(sf::Vector2f(rect.left, rect.top));
    buttonTexture = sf::Texture();
    if (ui)
	{
		ui->addListener(this);
	}else{
		cout << "Button: A UI object shouldn't be created without a valid UI reference";
	}
}

void Button::setPosition(sf::Vector2f newPosition){
    transform.setPosition(newPosition);
    buttonShape.setPosition(newPosition);
}

void Button::setRotation(float newRotation){
    buttonShape.setRotation(newRotation);
}

void Button::setSize(const sf::Vector2f &newSize){
    Placeable::setSize(newSize);
    buttonShape.setSize(newSize);
    buttonShape.setOrigin(size/2.0f);
    buttonShape.setPosition(getPosition());
}

bool Button::OnMouseButtonDown(){
    //we wouldnt want our mdown-callback to change the handlevent param before returning
    bool returnValue = handleEvent;
    isPressed = true;
    if (onMouseDownCallback){
        (*onMouseDownCallback)();
    }else{
        cout << "Button: MouseDown-callback isn't configured yet!\n";
    }
    return returnValue;
}

bool Button::OnMouseButtonUp(){
    //we wouldnt want our mup-callback to change the handlevent param before returning
    bool returnValue = handleEvent;
    isPressed = false;
    if (onMouseUpCallback){
        (*onMouseUpCallback)();
    }else{
        cout << "Button: MouseUp-callback isn't configured yet!\n";
    }
    return returnValue;
}
    
bool Button::OnBeginMouseover(){
    bool returnValue = handleEvent;
    buttonShape.setFillColor(mouseOverColor);
    if (onBeginMouseoverCallback){
        (*onBeginMouseoverCallback)();
    }else{
        cout << "Button: Mouseover-callback isn't configured yet!\n";
    }
    return returnValue;
}

bool Button::OnEndMouseover(){
    bool returnValue = handleEvent;
    buttonShape.setFillColor(defaultColor);
    isPressed = false;
    if (onEndMouseoverCallback){
        (*onEndMouseoverCallback)();
    }else{
        cout << "Button: Mouseout-callback isn't configured yet!\n";
    }
    return returnValue;
}