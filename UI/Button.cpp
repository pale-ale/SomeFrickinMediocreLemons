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
		cout << "added button as listener.\n";
	}else{
		cout << "a UI object shouldn't be created without a valid UI reference";
	}
}

void Button::setPosition(sf::Vector2f newPosition){
    transform.setPosition(newPosition);
    buttonShape.setPosition(newPosition);
}

void Button::setRotation(float newRotation){
    buttonShape.setRotation(newRotation);
}

/*void Button::setSize(sf::Vector2f newSize){
    buttonShape.setSize(newSize);
    size = newSize;
}*/

bool Button::OnMouseButtonDown(){
    //we wouldnt want our mdown-callback to change the handlevent param before returning
    bool returnValue = handleEvent;
    isPressed = true;
    if (onMouseDownCallback){
        (*onMouseDownCallback)();
    }else{
        cout << "MouseDown-callback isn't configured yet!\n";
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
        cout << "MouseUp-callback isn't configured yet!\n";
    }
    return returnValue;
}
    
bool Button::OnBeginMouseover(){
    bool returnValue = handleEvent;
    if (onBeginMouseoverCallback){
        (*onBeginMouseoverCallback)();
    }else{
        cout << "Mouseover-callback isn't configured yet!\n";
    }
    return returnValue;
}

bool Button::OnEndMouseover(){
    bool returnValue = handleEvent;
    isPressed = false;
    //what the fuck is this can't execute this function without callback wtf
    if (onEndMouseoverCallback){
        (*onEndMouseoverCallback)();
    }else{
        cout << "Mouseout-callback isn't configured yet!\n";
    }
    return returnValue;
}