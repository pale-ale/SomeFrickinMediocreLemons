#pragma once

class Settings{
    public:
    static const unsigned int defaultWidth = 400;
    static const unsigned int defaultHeight = 240;
    inline static const char* defaultFontPaths[] = {"/usr/share/fonts/truetype/ubuntu/UbuntuMono-R.ttf",
                                                    "/usr/share/fonts/noto/NotoSerif-Regular.ttf"};
    inline static const char* validFontPath = nullptr;
    inline static const int StartLifePoints = 4000;
    static const bool bEnableButtonTint = false;
    inline static const sf::Color BlackColor = {255,0,0,255};
    inline static const sf::Color BlueColor = {255,0,0,255};
    inline static const sf::Color GreenColor = {255,0,0,255};
    inline static const sf::Color RedColor = {255,0,0,255};
    inline static const sf::Color WhiteColor = {255,0,0,255};
};
