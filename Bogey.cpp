#include "Bogey.h"

void Bogey::bogeyUpdate() {
    move(speed);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && getPosLeft() > 0)
        setSpeedX(-bogeySpeed);
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && getPosRight() < windowWidth)
        setSpeedX(bogeySpeed);
    else
        setSpeedX(0);
}
