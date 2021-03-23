#pragma once

#include <algorithm>
#include <cmath>
#include "CardSelectionInfo.h"
#include <iostream>
#include <list>
#include <SFML/Graphics.hpp>
#include "Battlefield.h"
#include "Hand.h"
#include "ManaType.h"
#include "UI/PlayerHUD.h"
#include "Settings.h"
#include "UI/Bar.h"
#include "UI/CardSelector.h"
#include "UI/ManaBars.h"


class card;
class Game;

using std::shared_ptr;
using namespace std;

class Player: public UIElement{
    private:
    list<shared_ptr<card>> deck = {};
    list<shared_ptr<card>> graveyard = {};
    const sf::Vector2f deckOffset = {-163,-50};
    const sf::Vector2f handOffset = {0,50};
    const sf::Vector2f lifePointOffset = {125,-30};
    const sf::Vector2f manaBarOffset = {-132, -35};
    const sf::Vector2f graveyardOffset = {163,-50};
    const sf::Vector2f battlefieldOffset = {0,-125};
	FMana mana;
	string name;	
    Game* game = nullptr;
    int lifePoints=Settings::StartLifePoints;

    public:
	Player(UISystem* ui, string name);
	Player(UISystem* ui);
    void setGame(Game* newGame){game = newGame;};
    Game* getGame(){return game;};
    void drawCards(const int count);
    void playCard(card *card);
    void previewCard(const card* cardToPreview);
    void stopPreviewingCard();
    void cardSelectionUpdated(){
        cout << "carsel\n";
        if (awaitingSelection){
            cout << "carsel\n";
            awaitingSelection->onReceiveSelection(cardSelector->getSelectedCards());
            cardSelector->resetSelection();
            awaitingSelection = nullptr;
        }
    };
    card* awaitingSelection = nullptr;
    void addCardToDeck(shared_ptr<card> card);
    shared_ptr<card> removeCardFromDeck(card* card);
    shared_ptr<card> removeCardFromDeckTop();
    void addCardToGraveyard(shared_ptr<card> card);
    const list<card*> getHand() const;
    void printDeck() const;
    void printHand() const;
	void addMana(int amount, EManaType color);
	void addMana(const FMana& m);
    const FMana getMana() const {return mana;}
	void clearMana();
    string getName(){return name;}
    bool bIsMyTurn;
    void startSelection(CardSelectionInfo cardSelectionInfo);
    std::shared_ptr<Hand> playerhand;
    std::shared_ptr<Battlefield> battlefield;
    std::shared_ptr<PlayerHUD> playerHud;
    std::shared_ptr<Bar> playerBar;
    std::shared_ptr<ManaBars> playerManaBars;
    std::shared_ptr<CardSelector> cardSelector;
    int getLifePoints();
    void setLifePoints(int);
    virtual void initializeSubComponents() override;
    
    protected:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates state) const override{
        UIElement::draw(target, state);
    }
};
