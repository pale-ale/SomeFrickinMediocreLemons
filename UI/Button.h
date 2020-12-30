#include <iostream>
#include "UISystem.h"
#include <SFML/Graphics.hpp>

class Button : public UIElement{
    public:
    Button(sf::Rect<float> rect = {0,0,50,50});
    virtual void OnMouseButtonDown(sf::Event)override{cout << "I was clicked!\n";}
    
    protected:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates state) const override{
        target.draw(buttonShape);
    }

    private:
    sf::Rect<float> rect;
    sf::RectangleShape buttonShape;
    sf::Sprite buttonSprite;
    sf::Texture buttonTexture;
};