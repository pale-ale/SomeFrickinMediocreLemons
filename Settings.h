#pragma once
#include <SFML/Graphics.hpp>

class Settings{
    public:
    static const unsigned int defaultWidth = 400;
    static const unsigned int defaultHeight = 240;
    inline static const char* programDir = nullptr;
    inline static const char* defaultFontPaths[] = {"/usr/share/fonts/truetype/noto/NotoMono-Regular.ttf",
                                                    "/usr/share/fonts/truetype/ubuntu/UbuntuMono-R.ttf",
                                                    "/usr/share/fonts/noto/NotoSerif-Regular.ttf"};
    inline static const char* relativeAssetCardPath = "assets/cardTextures/";
    inline static const char* relativeAssetCardFront = "CardFront.png";
    inline static const char* relativeAssetCardBack = "CardBack.png";
    inline static const char* relativeAssetTabletopPath = "assets/Tabletop.png";
    inline static const char* validFontPath = nullptr;
    inline static const int StartLifePoints = 4000;
    static const int fontSize = 10;
    static const bool bEnableButtonTint = false;
    static const bool bDrawDebugHitbox = false;
    inline static const sf::Vector2f cardScale = {0.75, 0.75};    
    inline static const sf::Vector2f cardSize = {50, 75};
    inline static const sf::Color darkGrayColor = {50,50,50,255};
    inline static const sf::Color blackColor = {0,0,0,255};
    inline static const sf::Color blueColor = {32,192,255,255};
    inline static const sf::Color greenColor = {128,255,0,255};
    inline static const sf::Color redColor = {255,0,0,255};
    inline static const sf::Color whiteColor = {255,255,248,255};
};
