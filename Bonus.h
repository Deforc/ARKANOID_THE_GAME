#ifndef ARKANOID_THE_GAME_BONUS_H
#define ARKANOID_THE_GAME_BONUS_H
#include <SFML/Graphics.hpp>
#include "Ball.h"
#include "Bogey.h"
#include "Block.h"
#include "Options.h"
#include "Rectangle.h"
#include <memory>
#include <utility>

class Bonus : public Rectangle {
public:
    Bonus(float x, float y) : Rectangle(x, y, bonusX, bonusY, 0, bonusSpeed, sf::Color::White) {}

    enum class bonusState {
        NONE, RECEIVED, MOVING, FAILED
    };

    void setBonusPos(float x, float y) { this->bonusPos = {x, y}; }

    bonusState getBonusState() { return this->bonusstate; }
    void setBonusState (bonusState bonusstate) { this->bonusstate = bonusstate; }

    virtual void effect() {std::cout << "base work" << std::endl;};

    void bonusUpdate();

private:
    sf::Vector2f bonusPos { 0,0 };
    bonusState bonusstate = bonusState::NONE;
};

class BonusChangeSize : public Bonus {
public:
    BonusChangeSize(float x, float y, Bogey* bogey) : Bonus(x, y) { this->bogey = bogey; };
    void effect() override {
        bogey->setBogeySize();
        bogey->setOrigin(bogey->getSize().x / 2.f, bogey->getSize().y / 2.f);
    }
private:
    Bogey* bogey;
};
class BonusChangeSpeed : public Bonus {
public:
    BonusChangeSpeed(float x, float y, std::vector<Ball>* balls) : Bonus(x, y) {this->balls = balls; }
    void effect() override {
        for(auto& ball : *balls)
            ball.setSpeed({ ball.getSpeed().x * ballSpeedBonus, ball.getSpeed().y * ballSpeedBonus});
    }

private:
    std::vector<Ball>* balls;
};
class BonusBall : public Bonus {
public:
    BonusBall(float x, float y,  std::vector<Ball>* balls) : Bonus(x, y) { this->balls = balls; };
    void effect() override {
        balls->emplace_back(windowWidth / 2, 3 * windowHeight / 4, sf::Color::White);
    }
private:
    std::vector<Ball>* balls;
};

class BonusSavingBottom : public Bonus {
public:
    BonusSavingBottom(float x, float y, std::unique_ptr<Block>* savingblock) : Bonus(x, y) { this->savingblock = savingblock;}
    void effect() override {
        if(*savingblock == nullptr)
        {
            *savingblock = std::unique_ptr<Block>(new SavingBlock(windowWidth / 2, windowHeight - savingBottomHeight, sf::Color::White));
        }
    }
private:
    std::unique_ptr<Block>* savingblock;
};
class BonusStickiness : public Bonus {
public:
    BonusStickiness(float x, float y,  std::vector<Ball>* balls, Bogey* bogey) : Bonus(x, y) {
        this->balls = balls;
        this->bogey = bogey;
    };
    void effect() override {
        for(auto &ball : *balls)
            ball.setStickiness(true);
        bogey->setStickiness(true);

    }
private:
    std::vector<Ball>* balls;
    Bogey* bogey;
};

#endif //ARKANOID_THE_GAME_BONUS_H
