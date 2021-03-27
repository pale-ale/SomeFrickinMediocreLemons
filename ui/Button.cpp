#include "Button.h"

Button::Button(UISystem* ui, sf::Rect<float> rect, sf::Color color):
UIElement(ui){
    size = sf::Vector2f(rect.width, rect.height);
    Placeable::setSize(size);
    setName("Button");
    this->rect = rect;
    buttonShape = sf::RectangleShape(size);
    buttonShape.setFillColor(color);
    buttonShape.setOrigin(size/2.0f);
    transform.setPosition(sf::Vector2f(rect.left, rect.top));
    buttonTexture = sf::Texture();
}

void Button::initializeSubComponents(){
    UIElement::initializeSubComponents();
    if (ui)
	{
		ui->addListener(static_pointer_cast<UIElement>(shared_from_this()));
	}else{
		cout << "Button: A UI object shouldn't be created without a valid UI reference";
	}
}


void Button::setPosition(const sf::Vector2f &newPosition){
    UIElement::setPosition(newPosition);
    transform.setPosition(newPosition);
    buttonShape.setPosition(newPosition);
}

void Button::setRotation(const float &newRotation){
    UIElement::setRotation(newRotation - getRotation());
    buttonShape.setRotation(newRotation);
}

void Button::setSize(const sf::Vector2f &newSize){
    Placeable::setSize(newSize);
    buttonShape.setSize(newSize);
    buttonShape.setOrigin(size/2.0f);
    buttonShape.setPosition(getPosition());
}

bool Button::OnMouseButtonDown(){
    UIElement::OnMouseButtonDown();
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
    UIElement::OnMouseButtonUp();
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
    UIElement::OnBeginMouseover();
    bool returnValue = handleEvent;
    buttonShape.setFillColor(mouseOverColor);
    if (onBeginMouseoverCallback){
        (*onBeginMouseoverCallback)();
    }else{
        cout << name << ": Mouseover-callback isn't configured yet!\n";
    }
    return returnValue;
}

void Button::OnClick(){
    UIElement::OnClick();
    if (onClickCallback){
        (*onClickCallback)();
        return;
    }
    cout << name << ": Click-callback isn't configured yet!\n";
}
void Button::OnDragStart(){
    UIElement::OnDragStart();
    if (onDragStartCallback){
        (*onDragStartCallback)();
        return;
    }
    cout << "Button: DragStart-callback isn't configured yet!\n";
}
void Button::OnDragMove(const sf::Vector2f &newPos){
    UIElement::OnDragMove(newPos);
    if (onDragMoveCallback){
        (*onDragMoveCallback)(newPos);
        return;
    }
    cout << "Button: DragMove-callback isn't configured yet!\n";
}
void Button::OnDragEnd(){
    UIElement::OnDragEnd();
    if (onDragEndCallback){
        (*onDragEndCallback)();
        return;
    }
    cout << "Button: DragEnd-callback isn't configured yet!\n";
}

bool Button::OnEndMouseover(){
    UIElement::OnEndMouseover();
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