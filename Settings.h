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
};
