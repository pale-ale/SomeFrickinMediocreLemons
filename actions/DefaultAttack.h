#include "../IAction.h"
#include <string>
#include <iostream>

using std::string;

class DefaultAttack : public IAction{
    public:
    DefaultAttack(){
        if (!image.loadFromFile(Settings::programDir + string(Settings::relativeAssetActionPath) + "DefaultAttackAction.png")){
            cout << "DefaultAttackAction: Error loading image '" << 
            Settings::programDir + string(Settings::relativeAssetActionPath) + "DefaultAttackAction.png" << "'.";
        }
    }
    sf::Texture const &getActionImage() const override{
        return image;
    }
    std::string getActionString() const override{
        return text;
    }
    bool getActionEnabled() const override{
        return bIsEnabled;
    }
    void triggerAction() override{
        std::cout << "Attacking!\n";
    };

    private:
    sf::Texture image;
    std::string text = "Attack";
    bool bIsEnabled = true;
};