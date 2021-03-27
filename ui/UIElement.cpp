#include "UIElement.h"

void UIElement::draw(sf::RenderTarget &target, sf::RenderStates state) const
{
    Placeable::draw(target, state);
};
