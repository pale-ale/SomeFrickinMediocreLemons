#include "card.h"
void card::moveGraveyard(){
	graveyard=true;
}
bool card::checkGraveyard(){
	return graveyard;
}
string card::getType(){
	return type;
}
string card::getName(){
	return name;
}
card::card (std::string Type, string Name){
	this->type=Type;
	this->name=Name;
	this->graveyard=false;
}
