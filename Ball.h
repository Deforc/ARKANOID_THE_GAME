#ifndef ARKANOID_THE_GAME_BALL_H
#define ARKANOID_THE_GAME_BALL_H
#include <SFML/Graphics.hpp>
#include "Options.h"
#include "Statistics.h"


class Ball : public sf::CircleShape {
public:
    Ball(float x, float y, sf::Color color);
    ~Ball() = default;
    float getPosLeft() { return this->getPosition().x - this->getRadius(); }
    float getPosRight() { return this->getPosition().x + this->getRadius(); }
    float getPosTop() { return this->getPosition().y - this->getRadius(); }
    float getPosBottom() { return this->getPosition().y + this->getRadius(); }
    sf::Vector2f getSpeed() { return this->speed; }

    void setSpeed(sf::Vector2f speed) { this->speed = speed; }
    void setSpeedX(float speedX) { speed.x = speedX; }
    void setSpeedY(float speedY) { speed.y = speedY; }

    void ballUpdate(Statistics& stats);

    bool getStickiness() {return ballStickiness;}
    void setStickiness(bool stickiness) {ballStickiness = stickiness;}
private:
    sf::Vector2f speed {-ballSpeed, -ballSpeed};
    bool ballStickiness = false;
};


#endif //ARKANOID_THE_GAME_BALL_H
