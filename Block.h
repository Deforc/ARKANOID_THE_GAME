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
    float getSpeedBonus() const { return speedBonus; }

    void setSpeedBonus(float speedBonus) { this->speedBonus = speedBonus; }
    virtual void destroy () { isDeleted = true; }

protected:
    bool isDeleted = false;
    float speedBonus = 1.0f; // не нужен

};

class UndestroyableBlock : public Block {
public:
    UndestroyableBlock(float x, float y, sf::Color blockColor) : Block (x, y , blockColor) {}
    void destroy() override {}

};

class TankBlock : public Block {
public:
    TankBlock(float x, float y, sf::Color blockColor) : Block (x, y , blockColor) {}
    void destroy() override { if(hp==0) isDeleted = true; else hp--; }
private:
    int hp = 3;
};

class SpeedBlock : public Block {
public:
    SpeedBlock(float x, float y, sf::Color blockColor, float speedBonus) : Block (x, y , blockColor) {
        this->speedBonus = speedBonus;
    }
private:
    float speedBonus = 1.0f;
};

class BonusBlock : public Block {
public:
    BonusBlock(float x, float y, sf::Color blockColor) : Block (x, y , blockColor) {}
};

class SavingBlock : public Block {
public:
    SavingBlock(float x, float y, sf::Color blockColor) : Block (x, y, windowWidth, savingBottomHeight, blockColor) {}

};

#endif //ARKANOID_THE_GAME_BLOCK_H
