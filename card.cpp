#include "card.h"
void card::movegraveyard () {
	graveyard=true;
}
bool card::checkgraveyard () {
	return graveyard;
}
std::string card::gettype () {
	return type;
}
std::string card::getname () {
	return name;
}
card::card (std::string Type, std::string Name){
	card::type=Type;
	card::name=Name;
	card::graveyard=false;
}
	
