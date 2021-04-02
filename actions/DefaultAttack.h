#include "../IAction.h"
#include <string>
#include <iostream>

using std::string;

class DefaultAttack : public IAction{
    public:
    DefaultAttack(){
        image.loadFromFile(Settings::programDir + string(Settings::relativeAssetActionPath) + "DefaultAttackAction.png");
    }
    private:
    sf::Texture image;
    std::string text = "Attack";
    bool bIsEnabled = true;

    public:
    sf::Texture getActionImage() override{
        return image;
    }
    std::string getActionString() override{
        return text;
    }
    bool getActionEnabled() override{
        return bIsEnabled;
    }
    void triggerAction() override{
        std::cout << "Attacking!\n";
    };
};