#include "Rectangle.h"

Rectangle::Rectangle(float x, float y, float rectX, float rectY, float speedX, float speedY, sf::Color color)
            : speed({speedX, speedY}){
    setPosition(x, y);
    setSize({rectX, rectY});
    setFillColor(color);
    setOrigin(rectX / 2.f, rectY / 2.f);
}
