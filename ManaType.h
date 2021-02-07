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
        return Black>a.Black || Blue>a.Blue || Green>a.Green || Red>a.Red || White>a.White;
    }
    void add(EManaType color, int amount){
        get(color) = max(get(color) + amount, 0);
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
