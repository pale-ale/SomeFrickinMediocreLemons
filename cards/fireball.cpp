#include "fireball.h"

bool starteffect(card *card){
	if(card->getType()==cardType::MagicCard){
		card->moveGraveyard();
	}
	return true;
}
