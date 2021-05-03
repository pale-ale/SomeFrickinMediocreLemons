#pragma once

class Settings{
    public:
    static const unsigned int defaultWidth = 400;
    static const unsigned int defaultHeight = 240;
    inline static const char* programDir = nullptr;
    inline static const char* defaultFontPaths[] = {"/usr/share/fonts/truetype/noto/NotoMono-Regular.ttf",
                                                    "/usr/share/fonts/truetype/ubuntu/UbuntuMono-R.ttf",
                                                    "/usr/share/fonts/noto/NotoSerif-Regular.ttf"};
    inline static const char* relativeAssetCardPath = "assets/cardTextures/";
    inline static const char* relativeAssetActionPath = "assets/actionTextures/";
    inline static const char* relativeAssetCardFront = "CardFront.png";
    inline static const char* relativeAssetCardBack = "CardBack.png";
    inline static const char* relativeAssetTabletopPath = "assets/Tabletop.png";
    inline static const char* validFontPath = nullptr;
    inline static const char* logFileName = "log.txt";
    inline static const int StartLifePoints = 10;
    static const int fontSize = 10;
    static const bool bEnableButtonTint = false;
    static const bool bDrawDebugHitbox = false;
    inline static const float cardScaleX = 0.75;    
    inline static const float cardScaleY = 0.75;    
    inline static const float cardSizeX = 50;
    inline static const float cardSizeY = 75;
};
