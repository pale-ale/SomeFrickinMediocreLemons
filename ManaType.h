enum EManaType{
    Black,
    Blue,
    Green,
    Red,
    White    
};

struct FMana{
    public:
    int Black, Blue, Green, Red, White;
    FMana& operator +(const FMana& a){
        FMana m={Black+a.Black, Blue+a.Blue, Green+a.Green, Red+a.Red, White+a.White};
        return m;
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
        }
    }
};