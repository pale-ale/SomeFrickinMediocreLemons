#pragma once

#include <algorithm>
#include "Battlefield.h"
#include <cmath>
#include "CardSelectionInfo.h"
#include "Hand.h"
#include <iostream>
#include <list>
#include "ManaType.h"
#include <SFML/Graphics.hpp>
#include "Settings.h"
#include "ui/PlayerHUD.h"
#include "ui/Bar.h"
#include "ui/CardSelector.h"
#include "ui/ManaBars.h"


class Card;
class Game;

using std::shared_ptr;
using namespace std;

class Player: public UIElement{
    private:
    list<shared_ptr<Card>> deck = {};
    list<shared_ptr<Card>> graveyard = {};
    const sf::Vector2f deckOffset = {-163,-50};
    const sf::Vector2f handOffset = {0,50};
    const sf::Vector2f lifePointOffset = {125,-30};
    const sf::Vector2f manaBarOffset = {-132, -35};
    const sf::Vector2f graveyardOffset = {163,-50};
    const sf::Vector2f battlefieldOffset = {0,-125};
	FMana mana;
    Game* game = nullptr;
    int lifePoints=Settings::StartLifePoints;

    public:
	Player(UISystem* ui, string name);
	Player(UISystem* ui);
    void setGame(Game* newGame){game = newGame;};
    Game* getGame(){return game;};
    void drawCards(const int count);
    void playCard(Card *card, int slot = -1);
    void previewCard(const Card* cardToPreview);
    void selectCard(const Card* cardToSelect);
    void stopPreviewingCard();
    void cardSelectionUpdated(){
        if (awaitingSelection){
            awaitingSelection->onReceiveSelection(cardSelector->getSelectedCards());
            cardSelector->resetSelection();
            awaitingSelection = nullptr;
        }
    };
    Card* awaitingSelection = nullptr;
    void addCardToDeck(shared_ptr<Card> card);
    shared_ptr<Card> removeCardFromDeck(Card* card);
    shared_ptr<Card> removeCardFromDeckTop();
    void addCardToGraveyard(shared_ptr<Card> card);
    const list<Card*> getHand() const;
    void printDeck() const;
    void printHand() const;
	void addMana(int amount, EManaType color);
	void addMana(const FMana& m);
    const FMana getMana() const {return mana;}
	void clearMana();
    bool bIsMyTurn = false;
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
