#include "Kalle.h"
Kalle::Kalle() : card::card()
{
    pathToImage = "/usr/share/test/resources/Fireball.png";
    description = "heals 2000 life\npoints!";
    updateCardImage();
    SetupButtonBinding();
}
