#include "../IAction.h"
#include <string>
#include <iostream>

class VinesnatcherTap : public IAction{
    VinesnatcherTap(){
        image.loadFromFile("VinesnatcherTapTexture.png");
    }
    private:
    sf::Texture image;
    std::string text = "Tap";
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
        std::cout << "aciton proc'd\n";
    };
};