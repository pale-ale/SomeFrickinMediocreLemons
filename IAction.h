#include <SFML/Graphics.hpp>
#include <string>

class IAction{
    public:
    virtual sf::Texture getActionImage() = 0;
    virtual std::string getActionString() = 0;
    virtual bool getActionEnabled() = 0;
    virtual void triggerAction() = 0;
};