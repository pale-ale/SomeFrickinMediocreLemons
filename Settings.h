#pragma once
#include <SFML/Graphics.hpp>

class Settings{
    public:
    static const unsigned int defaultWidth = 400;
    static const unsigned int defaultHeight = 240;
    inline static const char* defaultFontPaths[] = {"/usr/share/fonts/truetype/noto/NotoMono-Regular.ttf",
                                                    "/usr/share/fonts/truetype/ubuntu/UbuntuMono-R.ttf",
                                                    "/usr/share/fonts/noto/NotoSerif-Regular.ttf"};
    inline static const char* assetCardPath = "../assets/cardTextures/";
    inline static const char* assetCardFront = "CardFront.png";
    inline static const char* assetCardBack = "CardBack.png";
    inline static const char* assetTabletopPath = "../assets/Tabletop.png";
    inline static const char* validFontPath = nullptr;
    inline static const int StartLifePoints = 4000;
    static const int fontSize = 10;
    static const bool bEnableButtonTint = false;
    static const bool bDrawDebugHitbox = false;
    inline static const sf::Color DarkGrayColor = {50,50,50,255};
    inline static const sf::Color BlackColor = {0,0,0,255};
    inline static const sf::Color BlueColor = {32,192,255,255};
    inline static const sf::Color GreenColor = {128,255,0,255};
    inline static const sf::Color RedColor = {255,0,0,255};
    inline static const sf::Color WhiteColor = {255,255,248,255};
};
