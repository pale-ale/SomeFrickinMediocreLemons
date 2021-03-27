#pragma once
#include "../Placeable.h"

class UISystem;

class UIElement : public Placeable
{
protected:
    UIElement() = delete;
    UIElement(UISystem *ui) : ui{ui} {};

public:
    virtual bool OnMouseButtonDown() { return false; }
    virtual bool OnMouseButtonUp() { return false; }
    virtual void OnClick() {cout << "UIElement: Got clicked\n";}
    virtual void OnDragStart(){ cout << "UIElement: Getting dragged\n";}
    virtual void OnDragMove(const sf::Vector2f &newMouseLocation){}
    virtual void OnDragEnd(){ cout << "UIElement: Drag released\n";}
    virtual bool OnBeginMouseover()
    {
        cout << "UIElement: Mouseover\n";
        return false;
    }
    virtual bool OnEndMouseover()
    {
        cout << "UIElement: Mouseout\n";
        return false;
    }
    UISystem *ui = nullptr;
    bool isDragable = false;
    bool isMouseovering = false;
    bool isVisible = true;

    virtual void draw(sf::RenderTarget &target, sf::RenderStates state) const override;
};
