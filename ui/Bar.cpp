#include "Bar.h"
#include "../Player.h"

Bar::Bar(UISystem* ui, int width, int height, sf::Color bgColor, sf::Color fgColor):
Bar(ui)
{
    barSize.x = width;
    barSize.y = height;
    this->BGColor = bgColor;
    this->FGColor = fgColor;
}
Bar::Bar(UISystem* ui, sf::Color bgColor, sf::Color fgColor, int rotation):
Bar(ui)
{
    this->BGColor = bgColor;
    this->FGColor = fgColor;
    setRotation(rotation);
}
Bar::Bar(UISystem* ui, int width, int height):
Bar(ui)
{
    barSize.x = width;
    barSize.y = height;
}
Bar::Bar(UISystem* ui):
UIElement(ui)
{
    size=barSize;
    name = "Bar";
    setDimensions(barSize-offset);
    font->loadFromFile(Settings::validFontPath);
    BarInfo.setFont(*font);
    BarInfo.setCharacterSize(this->fontsize);
    BarInfo.setRotation(textRotation);
    BarInfo.setScale(.35f,.35f);
}

void Bar::initializeSubComponents(){
    UIElement::initializeSubComponents();
    ui->addListener(static_pointer_cast<UIElement>(weak_from_this().lock()));
}

void Bar::updateBG(){
    Background.setSize(barSize);
    Background.setOrigin(barSize / 2.0f);
    Background.setPosition(getPosition());
    Background.setFillColor(BGColor);
    size=barSize;
}

void Bar::updateFG(){
    float fgHeight = barSize.y - 2*offset.y;
    float fgWidth = (barSize.x - 2*offset.y) * amount;
    float fgOrigY = barSize.y / 2.0f - offset.y;
    float fgOrigX = barSize.x / 2.0f - offset.x;
    Foreground.setSize({fgWidth, fgHeight});
    Foreground.setOrigin({fgOrigX, fgOrigY});
    Foreground.setPosition(getPosition());
    Foreground.setFillColor(FGColor);
    size=barSize;
}

void Bar::setDimensions(sf::Vector2f dimensions)
{
    barSize = dimensions;
    setHitbox({dimensions*-.5f, {dimensions.x*-.5f, dimensions.y*.5f}, dimensions*.5f,
               {dimensions.x*.5f, dimensions.y*-.5f}});
    updateBG();
    updateFG();
}

void Bar::draw(sf::RenderTarget &target, sf::RenderStates state) const
{
    target.draw(Background);
    target.draw(Foreground);
    target.draw(BarInfo);
    UIElement::draw(target, state);
}

void Bar::setFillFactor(float newfactor)
{
    factor = newfactor;
    amount = std::min(std::max(0.0f, factor), 1.0f);
    updateFG();
}

void Bar::setFGColor(sf::Color Color)
{
    Foreground.setFillColor(Color);
    FGColor = Color;
}

sf::Color Bar::getFGColor()
{
    return this->FGColor;
}

void Bar::setBGColor(sf::Color Color)
{
    Background.setFillColor(Color);
    this->BGColor = Color;
}

void Bar::setPosition(const sf::Vector2f &newPosition)
{
    UIElement::setPosition(newPosition);
    Background.setPosition(newPosition);
    Foreground.setPosition(newPosition);
    auto t = sf::Transform().rotate(getRotation()).transformPoint(sf::Vector2f{barSize.x/2, 0} + textOffset);
    BarInfo.setPosition(getPosition() + t);    
    updateBG();
    updateFG();
}

void Bar::setRotation(const float &newRotation)
{
    UIElement::setRotation(newRotation);
    Foreground.setRotation(newRotation);
    Background.setRotation(newRotation);
    auto t = sf::Transform().rotate(newRotation).transformPoint(sf::Vector2f{barSize.x/2, 0} + textOffset);
    BarInfo.setPosition(getPosition() + t);
    BarInfo.setRotation(newRotation);
    updateBG();
    updateFG();
}

bool Bar::OnBeginMouseover(){
    BarInfo.setString(to_string(lround(this->factor*Settings::StartLifePoints)) + "/" + to_string(Settings::StartLifePoints));
    return false;
}

bool Bar::OnEndMouseover(){
    BarInfo.setString("");
    return false;
}
