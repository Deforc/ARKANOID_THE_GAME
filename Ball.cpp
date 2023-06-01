#include "Ball.h"

Ball::Ball(float x, float y, sf::Color color) {
    setPosition(x, y);
    setRadius(ballRadius);
    setOrigin(ballRadius, ballRadius);
    setFillColor(color);
}

void Ball::ballUpdate(Statistics& stats) {
    move(speed);
    if (getPosLeft() < 0 || getPosRight() > windowWidth)
        speed.x = -speed.x;
    if (getPosTop() < 0)
        speed.y = -speed.y;
    else if (getPosBottom() > windowHeight) {
        if(stats.getHP() > 0)
            stats.hpPenalty();
        setPosition( windowWidth / 2 , windowHeight - 10 - bogeyY - getRadius());
        speed.y = -speed.y;
    }
}
