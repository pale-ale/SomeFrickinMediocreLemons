#include "card.h"
void card::movegraveyard () {
	graveyard=true;
}
bool card::checkgraveyard () {
	return graveyard;
}
string card::gettype () {
	return type;
}
string card::getname () {
	return name;
}
card::card (std::string Type, string Name){
	card::type=Type;
	card::name=Name;
	card::graveyard=false;
}
