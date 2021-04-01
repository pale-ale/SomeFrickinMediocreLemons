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
    MultiSelect(UISystem *ui) : UIElement(ui){}
    //add an optiono to select from.
    // text: the text to be displayed; 
    // positionPriority: lets you determine the order of elements. 10,11 will look the same as 0,1.
    void addOption(Option option);
    private:
    vector<sf::Vector2f> buttonHitboxEven = {{-9, -7}, {0, 7}, {9, -7}};
    vector<sf::Vector2f> buttonHitboxOdd = {{-9, 7}, {9, 7}, {0, -7}};
    sf::Vector2f offset = {20, 0};
    vector<Option> options;
    vector<shared_ptr<Button>> optionButtons;
};