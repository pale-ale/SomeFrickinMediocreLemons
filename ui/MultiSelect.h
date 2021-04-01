#include "UIElement.h"
#include "Button.h"
#include "../events/EventCallback.h"

struct Option{
    string text;
    shared_ptr<IEventCallback<>> callback = nullptr;
    int priority = 0;
};
class MultiSelect : public UIElement{
    public:
    MultiSelect(UISystem *ui) : UIElement(ui){labelFont.loadFromFile(Settings::validFontPath);}
    //add an optiono to select from.
    // text: the text to be displayed; 
    // positionPriority: lets you determine the order of elements. 10,11 will look the same as 0,1.
    void addOption(Option option);
    private:
    sf::Font labelFont;
    vector<sf::Vector2f> buttonHitboxEven = {{-9, -7}, {0, 7}, {9, -7}};
    vector<sf::Vector2f> buttonHitboxOdd = {{-9, 7}, {9, 7}, {0, -7}};
    sf::Vector2f offset = {20, 0};
    vector<Option> options;
    vector<shared_ptr<Button>> optionButtons;
    vector<shared_ptr<sf::Text>> optionLabels;
    protected:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates state) const override{
        UIElement::draw(target, state);
        for (auto label : optionLabels){
            target.draw(*label.get());
        }
    }
};