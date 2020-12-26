#include "card.h"
void card::movegraveyard () {
	graveyard=true;
}
std::string card::gettype () {
	return type;
}
bool card::checkgraveyard () {
	return graveyard;
}
card::card (std::string Type, std::string Name){
	card::type=Type;
	card::name=Name;
}
	
