#ifndef ARKANOID_THE_GAME_BONUS_H
#define ARKANOID_THE_GAME_BONUS_H
#include <SFML/Graphics.hpp>
#include "Ball.h"
#include "Bogey.h"
#include "Block.h"
#include "Options.h"
#include "Rectangle.h"


//enum class bonusType {
//    NONE, CHANGESIZE, CHANGESPEED, STICKINESS, SAVINGBOTTOM, BONUSBALL
//};


class Bonus : public Rectangle {
public:
    Bonus(float x, float y) : Rectangle(x, y, bonusX, bonusY, 0, bonusSpeed, sf::Color::White) {}

    enum class bonusState {
        NONE, RECEIVED, MOVING, FAILED
    };
//    bool getStatus() const { return this->received; }
//    bool getMovingStatus() const { return this->moving; }
//    bool getFailStatus() const { return this->failed; }
//
//    void setStatus(bool status) { this->received = status; }
//    void setMovingStatus(bool status) { this->moving = status; }
//    void setFailStatus(bool status) { this->failed = status; }
    void setBonusPos(float x, float y) { this->bonusPos = {x, y}; }

//    bonusType getBonusType() { return this->bonustype; }
//    void setBonusType(bonusType bonustype) { this->bonustype = bonustype; }

    bonusState getBonusState() { return this->bonusstate; }
    void setBonusState (bonusState bonusstate) { this->bonusstate = bonusstate; }

    virtual void effect(std::vector<Ball>& balls, Block **savingBlock, Bogey& bogey) {std::cout << "base work" << std::endl;};

  //  void spawnBonusBall(std::vector<Ball>& balls);
  //  void spawnSavingBottom(Block& savingBottom);

    //void ballSpeedIncrease (float speedBonus) { ballSpeedBonus = speedBonus; }
   // void bogeyWidthIncrease(float widthBonus) { bogeyWidthBonus = widthBonus; }

   // void stickBallBogey ();

    void bonusUpdate();

private:
    sf::Vector2f bonusPos { 0,0 };
    //sf::Vector2f speed { 0, bonusSpeed };
//    bool received = false;
//    bool moving = false;
//    bool failed = false;
   // bonusType bonustype = bonusType::NONE;
    bonusState bonusstate = bonusState::NONE;
//    float ballSpeedBonus = 1.f;
 //   float bogeyWidthBonus = 1.f;
};

class BonusChangeSize : public Bonus {
public:
    BonusChangeSize(float x, float y) : Bonus(x, y) {};
    void effect(std::vector<Ball>& balls, Block **savingBlock, Bogey& bogey) override {
        bogey.setBogeySize();
        bogey.setOrigin(bogey.getSize().x / 2.f, bogey.getSize().y / 2.f);
    }
};
class BonusChangeSpeed : public Bonus {
public:
    BonusChangeSpeed(float x, float y) : Bonus(x, y) {};
    void effect(std::vector<Ball>& balls, Block **savingBlock, Bogey& bogey) override {
        for(auto& ball : balls)
            ball.setSpeed({ ball.getSpeed().x * ballSpeedBonus, ball.getSpeed().y * ballSpeedBonus});
    }
};
class BonusBall : public Bonus {
public:
    BonusBall(float x, float y) : Bonus(x, y) {};
    void effect(std::vector<Ball>& balls, Block **savingBlock, Bogey& bogey) override {
        balls.emplace_back(windowWidth / 2, 3 * windowHeight / 4, sf::Color::White);
    }
};

class BonusSavingBottom : public Bonus {
public:
    BonusSavingBottom(float x, float y) : Bonus(x, y) {};
    void effect(std::vector<Ball>& balls, Block** savingBlock, Bogey& bogey) override {
        std::cout << "1" << std::endl;
        if(*savingBlock == nullptr)
        {
            std::cout << "2" << std::endl;
            *savingBlock = new Block (windowWidth / 2, windowHeight - savingBottomHeight, windowWidth, savingBottomHeight, sf::Color::White);
            std::cout << "3" << std::endl;
        }
       // else
           // *savingBlock->setHP(*savingBlock->getHP() + 1);

    }
};
class BonusStickiness : public Bonus {
public:
    BonusStickiness(float x, float y) : Bonus(x, y) {};
    void effect(std::vector<Ball>& balls, Block **savingBlock, Bogey& bogey) override {
    }
};

#endif //ARKANOID_THE_GAME_BONUS_H
