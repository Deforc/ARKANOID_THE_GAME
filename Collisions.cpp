#include "Collisions.h"

bool BallRectIntersection(Rectangle& rect, Ball& ball) {
   return (rect.getPosRight() >= ball.getPosRight())
          && (rect.getPosLeft() <= ball.getPosRight())
          && (rect.getPosBottom() >= ball.getPosTop())
          && (rect.getPosTop() <= ball.getPosBottom());
}

bool BallBallIntersection(Ball& ball1, Ball& ball2) {
    return (ball1.getPosRight() >= ball2.getPosRight())
           && (ball1.getPosLeft() <= ball2.getPosRight())
           && (ball1.getPosBottom() >= ball2.getPosTop())
           && (ball1.getPosTop() <= ball2.getPosBottom());
}

bool RectRectIntersection (Rectangle& rect1, Rectangle& rect2) {
    return (rect1.getPosRight() >= rect2.getPosRight())
           && (rect1.getPosLeft() <= rect2.getPosRight())
           && (rect1.getPosBottom() >= rect2.getPosTop())
           && (rect1.getPosTop() <= rect2.getPosBottom());
}

void Collision (Bogey& bogey, std::vector<Ball>& balls) {
    for (auto& ball : balls) {
        if (BallRectIntersection(bogey, ball)) {
            if(ball.getStickiness() == true && bogey.getStickiness() == true)
            {
                ball.setSpeed({0,0});
                ball.setPosition(bogey.getPosition().x + 5, bogey.getPosition().y - 10);
            } else {
                ball.setSpeedY(-ballSpeed);
                if (ball.getPosition().x < bogey.getPosition().x) {
                    ball.setSpeedX(-ballSpeed);
                }
                else {
                    ball.setSpeedX(ballSpeed);
                }
            }

        }
    }
}

void Collision(Bogey& bogey, Bonus& bonus) {
    if (RectRectIntersection(bogey, bonus))
        bonus.setBonusState(Bonus::bonusState::RECEIVED);

}

void Collision(Ball& ball1, Ball& ball2) {
    if (!BallBallIntersection(ball1, ball2))
        return;

    float intersectionLeft = ball1.getPosRight() - ball2.getPosLeft();
    float intersectionRight = ball2.getPosRight() - ball1.getPosLeft();
    float intersectionTop = ball1.getPosBottom() - ball2.getPosTop();
    float intersectionBottom = ball2.getPosBottom() - ball1.getPosTop();

    bool isBallOneFromLeft = abs(intersectionLeft) < abs(intersectionRight);
    bool isBallOneFromTop = abs(intersectionTop) < abs(intersectionBottom);

    float intersectionX = isBallOneFromLeft ? intersectionLeft : intersectionRight;
    float intersectionY = isBallOneFromTop ? intersectionTop : intersectionBottom;

    if (abs(intersectionX) < abs(intersectionY)) {
        ball1.setSpeedX(isBallOneFromLeft ? -abs(ball1.getSpeed().x) : abs(ball1.getSpeed().y));
        ball2.setSpeedX(isBallOneFromLeft ? abs(ball2.getSpeed().x) : -abs(ball2.getSpeed().y));
    }
    else {
        ball1.setSpeedY(isBallOneFromTop ? -abs(ball1.getSpeed().x) : abs(ball1.getSpeed().y));
        ball2.setSpeedY(isBallOneFromTop ? abs(ball2.getSpeed().x) : -abs(ball2.getSpeed().y));
    }


}

void Collision(Block& block, std::vector<Ball>& balls, Statistics& statistics, bool addScore) {
    for (auto& ball : balls) {
        if (BallRectIntersection(block, ball)) {
            if (block.getHP() > 0) {
                if(addScore)
                    statistics.scorePlusPlus();
                block.healthMinusMinus();
            }
            if (block.getDestroyability() && (block.getHP() == 0))
                block.setDeleted(true);

            if (block.getSpeedBonus() == 1.f)
                ball.setSpeed({ (ball.getSpeed().x > 0) ? ballSpeed : -ballSpeed,(ball.getSpeed().y > 0) ? ballSpeed : -ballSpeed });
            else ball.setSpeed({ ball.getSpeed().x * ballSpeedBonus, ball.getSpeed().y * ballSpeedBonus });


            float intersectionLeft = ball.getPosRight() - block.getPosLeft();
            float intersectionRight = block.getPosRight() - ball.getPosLeft();
            float intersectionTop = ball.getPosBottom() - block.getPosTop();
            float intersectionBottom = block.getPosBottom() - ball.getPosTop();

            bool isBallFromLeft(abs(intersectionLeft) < abs(intersectionRight));
            bool isBallFromTop(abs(intersectionTop) < abs(intersectionBottom));

            float intersectionX = isBallFromLeft ? intersectionLeft : intersectionRight;
            float intersectionY = isBallFromTop ? intersectionTop : intersectionBottom;

            if (abs(intersectionX) < abs(intersectionY)) {
                ball.setSpeedX(isBallFromLeft ? -abs(ball.getSpeed().x) : abs(ball.getSpeed().x));
            }
            else {
                ball.setSpeedY(isBallFromTop ? -abs(ball.getSpeed().y) : abs(ball.getSpeed().y));
            }
        }
    }
}