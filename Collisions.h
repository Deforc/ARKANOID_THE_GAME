#ifndef ARKANOID_THE_GAME_COLLISIONS_H
#define ARKANOID_THE_GAME_COLLISIONS_H
#include "Ball.h"
#include "Block.h"
#include "Bogey.h"
#include "Bonus.h"
#include "Statistics.h"
#include "Options.h"

bool BallRectIntersection(Rectangle& rect, Ball& ball);
bool BallBallIntersection(Ball& ball1, Ball& ball2);
bool RectRectIntersection (Rectangle& rect1, Rectangle& rect2);

void Collision(Bogey& bogey, std::vector<Ball>& balls);
void Collision(Bogey& bogey, Bonus& bonus);
void Collision(Ball& ball1, Ball& ball2);
void Collision(Block& block, std::vector<Ball>& balls, Statistics& statistics, bool addScore = true);

#endif //ARKANOID_THE_GAME_COLLISIONS_H
