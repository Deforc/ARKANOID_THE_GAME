#ifndef ARKANOID_THE_GAME_RECTANGLE_H
#define ARKANOID_THE_GAME_RECTANGLE_H
#include <SFML/Graphics.hpp>

class Rectangle : public sf::RectangleShape{
public:
    Rectangle(float x, float y, float rectX, float rectY, float speedX, float speedY, sf::Color color);

    float getPosLeft() { return getPosition().x - getSize().x / 2.f; }
    float getPosRight() { return getPosition().x + getSize().x / 2.f; }
    float getPosTop() { return getPosition().y - getSize().y / 2.f; }
    float getPosBottom() { return getPosition().y + getSize().y / 2.f; }
    sf::Vector2f getSpeed() { return speed; }
    //void setSpeed(sf::Vector2f speed) { this->speed = speed; }
    void setSpeedX(float speedX) { speed.x = speedX; }
    void setSpeedY(float speedY) { speed.x = speedY; }


protected:
    sf::Vector2f speed;
};


#endif //ARKANOID_THE_GAME_RECTANGLE_H
