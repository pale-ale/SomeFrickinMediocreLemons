#include "Button.h"
#include "../events/EventCallback.h"
#include "UISystem.h"

Button::Button(UISystem* ui, sf::Color defaultColor, sf::Color mouseOverColor, vector<sf::Vector2f> corners):
UIElement(ui), defaultColor{defaultColor}, mouseOverColor{mouseOverColor}{
    setName("Button");
    hitbox = corners;
    buttonTexture = sf::Texture();
    updateShape();
}

Button::~Button(){
    cout << "Button: Destroying button '" << name << "'.\n";
    if(ui){
        ui->removeEventListener(this);
    }
}

void Button::updateShape(){
    buttonShape.setPointCount(hitbox.size());
    buttonShape.setFillColor(defaultColor);
    auto& hb = getHitboxPolygonGlobal();
    for (int i = 0; i < hitbox.size(); i++)
    {
        buttonShape.setPoint(i, hb[i]);
    }
}

void Button::setHitbox(const vector<sf::Vector2f> &newHitbox){
    UIElement::setHitbox(newHitbox);
    updateShape();
}

void Button::initializeSubComponents(){
    UIElement::initializeSubComponents();
    if (ui)
	{
		ui->addEventListener(static_pointer_cast<UIElement>(shared_from_this()));
	}else{
		cout << "Button: A UI object shouldn't be created without a valid UI pointer\n";
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

void Button::setScale(float xScale, float yScale){
    UIElement::setScale(xScale, yScale);
    buttonShape.setScale({xScale, yScale});
}

bool Button::OnMouseButtonDown(const sf::Vector2f &mouseLocation){
    UIElement::OnMouseButtonDown(mouseLocation);
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

bool Button::OnMouseButtonUp(const sf::Vector2f &mouseLocation){
    UIElement::OnMouseButtonUp(mouseLocation);
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