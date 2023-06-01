#include "Bonus.h"

//void Bonus::spawnBonusBall(std::vector<Ball> &balls) {
//    balls.emplace_back(windowWidth / 2, 3 * windowHeight / 4, sf::Color::Magenta);
//}

//void Bonus::spawnSavingBottom(Block &savingBottom) {
//   // savingBottom.emplace_back(0, windowHeight - 2*savingBottomHeight, windowWidth, savingBottomHeight, sf::Color::White);
//    savingBottom = {0, windowHeight - 20 - savingBottomHeight, windowWidth, savingBottomHeight, sf::Color::White};
//}

void Bonus::bonusUpdate() {
    move(speed);
    if(getPosTop() > windowHeight)
        setBonusState(bonusState::FAILED);
}

//void Bonus::stickBallBogey() {
//    std::cout<< "Hi" << std::endl;
//}
