#include "fireball.h"
Fireball::Fireball() : card::card()
{
    pathToImage = "/usr/share/test/resources/Fireball.png";
    description="A fireball that attacks enemys";
    updateCardImage();
    SetupButtonBinding();
}
