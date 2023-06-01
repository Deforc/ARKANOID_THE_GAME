#include "Bonus.h"

void Bonus::bonusUpdate() {
    move(speed);
    if(getPosTop() > windowHeight)
        setBonusState(bonusState::FAILED);
}

