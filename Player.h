#pragma once

#include <algorithm>
#include <cmath>
#include <iostream>
#include <list>
#include <SFML/Graphics.hpp>

#include "ManaType.h"
#include "Settings.h"

#include "ui/Bar.h"
#include "ui/ManaBars.h"
#include "ui/PlayerHUD.h"

class Battlefield;
class Card;
class CardSelectionInfo;
class CardSelector;
class Game;
class Hand;
class IAction;
class PlayerCard;
class PlayerHUD;

using std::shared_ptr;
using namespace std;

class Player: public UIElement{
    private:
    list<shared_ptr<Card>> deck = {};
    list<shared_ptr<Card>> graveyard = {};
    shared_ptr<PlayerCard> playerCard;
    const sf::Vector2f deckOffset = {-163,-50};
    const sf::Vector2f handOffset = {0,50};
    const sf::Vector2f lifePointOffset = {125,-30};
    const sf::Vector2f manaBarOffset = {-132, -35};
    const sf::Vector2f graveyardOffset = {163,-50};
    const sf::Vector2f battlefieldOffset = {0,-125};
	FMana mana;
    const Card *selectedCard;
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
    const Card *getSelectedCard() const {return selectedCard;}
    void stopPreviewingCard();
    void cardSelectionUpdated();
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
    void startSelection(CardSelectionInfo cardSelectionInfo);
    int getLifePoints();
    void setLifePoints(int);
    virtual void initializeSubComponents() override;

    IAction* awaitingSelection = nullptr;
    bool bIsMyTurn = false;
    std::shared_ptr<Hand> playerhand;
    std::shared_ptr<Battlefield> battlefield;
    std::shared_ptr<PlayerHUD> playerHud;
    std::shared_ptr<Bar> playerBar;
    std::shared_ptr<ManaBars> playerManaBars;
    std::shared_ptr<CardSelector> cardSelector;
    
    protected:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates state) const override{
        UIElement::draw(target, state);
    }
};
