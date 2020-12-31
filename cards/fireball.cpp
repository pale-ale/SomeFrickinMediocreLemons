#include "fireball.h"
Fireball::Fireball():
card::card(){
    pathToImage = "/usr/share/test/resources/Fireball.png";
    updateCardImage();
    SetupButtonBinding();
}
