#ifndef ARKANOID_THE_GAME_BOGEY_H
#define ARKANOID_THE_GAME_BOGEY_H
#include <SFML/Graphics.hpp>
#include "Options.h"
#include "Rectangle.h"



class Bogey : public Rectangle {
public:
    Bogey(float x, float y) : Rectangle(x, y, bogeyX, bogeyY, -bogeySpeed, 0, sf::Color::White) {}
    void setBogeySize() { setSize({bogeyX+bogeyBonus, bogeyY});}
    void bogeyUpdate();

    bool getStickiness() {return bogeyStickiness;}
    void setStickiness(bool stickiness) {bogeyStickiness = stickiness;}
private:
    bool bogeyStickiness = false;
};


#endif //ARKANOID_THE_GAME_BOGEY_H
