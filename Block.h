#ifndef ARKANOID_THE_GAME_BLOCK_H
#define ARKANOID_THE_GAME_BLOCK_H
#include <SFML/Graphics.hpp>
#include "Options.h"
#include "Rectangle.h"


class Block : public Rectangle {
public:
    Block(float x, float y, sf::Color blockColor) : Rectangle(x, y, blockX, blockY, 0, 0, blockColor) {}
    Block(float x, float y, float saveWidth, float saveHeight, sf::Color blockColor) : Rectangle(x, y, saveWidth, saveHeight, 0, 0, blockColor) {
        setOrigin(saveWidth / 2.f, saveHeight /2.f);
    }

    bool getDeleted() const { return isDeleted; }
    bool getDestroyability() const { return destroyability; }
    float getSpeedBonus() const { return speedBonus; }
    int getHP() const { return healthpoint; }

    void setDeleted(bool isDeleted) { this->isDeleted = isDeleted; }
    void setDestroyability(bool destroyability1) { destroyability = destroyability1; }
    void setSpeedBonus(float speedBonus) { this->speedBonus = speedBonus; }
    void setHP(int hitAmount) { healthpoint = hitAmount; }
    void healthMinusMinus() { healthpoint--; }


protected:
    bool isDeleted = false;
    bool destroyability = true;
    float speedBonus = 1.0f;
    int healthpoint = 1;
};



#endif //ARKANOID_THE_GAME_BLOCK_H
