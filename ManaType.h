#pragma once
#include <iostream>

enum EManaType{
    Black,
    Blue,
    Green,
    Red,
    White    
};
// Black, Blue, Green, Red, White
struct FMana{
    public:
    int Black, Blue, Green, Red, White;
    FMana operator +(const FMana& a){
        return FMana{Black+a.Black, Blue+a.Blue, Green+a.Green, Red+a.Red, White+a.White};
    }
    bool operator >(const FMana& a){
        return Black>a.Black && Blue>a.Blue && Green>a.Green && Red>a.Red && White>a.White;
    }
    void add(EManaType color, int amount){
        get(color) = max(get(color) + amount, 0);
    }
    bool canAfford(const FMana& a) const{
        bool canAffordBlack = a.Black > 0 ? Black >= a.Black : true;
        bool canAffordBlue  = a.Blue  > 0 ? Blue  >= a.Blue  : true;
        bool canAffordGreen = a.Green > 0 ? Green >= a.Green : true;
        bool canAffordRed   = a.Red   > 0 ? Red   >= a.Red   : true;
        bool canAffordWhite = a.White > 0 ? White >= a.White : true;
        return canAffordBlack && canAffordBlue && canAffordGreen && canAffordRed && canAffordWhite;
    }

    private:
    int& get(EManaType color){
        switch (color)
        {
        case EManaType::Black:
            return Black;
        case EManaType::Blue:
            return Blue;
        case EManaType::Green:
            return Green;
        case EManaType::Red:
            return Red;
        case EManaType::White:
            return White;
        default:
            cout << "Bad mana type!\n";
            throw;
        }
    }
};
