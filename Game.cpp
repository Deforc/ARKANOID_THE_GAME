#include "Game.h"

void Game::Init() {

    window.create(sf::VideoMode(windowWidth, windowHeight), "Arkanoid");
    window.setFramerateLimit(120);

    setText();
    setBogey();
    setBalls();
    setBlocks();
    setBonuses();

}

void Game::setText() {

    font.loadFromFile("..\\EightBits.ttf");

    scoreText.setFillColor(sf::Color::White);
    scoreText.setFont(font);
    scoreText.setCharacterSize(70);
    scoreText.setPosition(20, 525);

    hpText.setFillColor(sf::Color::White);
    hpText.setFont(font);
    hpText.setCharacterSize(70);
    hpText.setPosition(20, 575);

    finalPhrase.setFont(font);
    finalPhrase.setCharacterSize(130);
    finalPhrase.setPosition(windowWidth/2, 3*windowHeight/4);

}

void Game::setBogey() {
    //bogey = {windowWidth/2, windowHeight - bogeyY - 30};
    bogey = Bogey(windowWidth/2, windowHeight - bogeyY - 30);
}

void Game::setBalls() {
    balls.emplace_back(windowWidth / 2  + 200, 3 * windowHeight / 4, sf::Color::White);
}


void Game::setBlocks() {
    //Generate simple blocks so that there is a distance between them for indestructible blocks
    for(int u = 1; u <= simpleBlockAmountX; u++)
        for(int v = 1; v <= simpleBlockAmountY; v++)
            simpleBlocks.emplace_back(u * (blockX + 70) + 10, (v+1)*(blockY + 25), sf::Color::Green);

    //Generate undestroyable blocks so that they are between simple ones
    for(int u = 0; u < undestroyableBlockAmountX; u++)
        for(int v = 0; v < undestroyableBlockAmountY; v++) {
            undestroyableBlocks.emplace_back((u+1) * (blockX + 70) + 75, (v+2)*(blockY + 25), sf::Color::Blue);
            undestroyableBlocks[u*undestroyableBlockAmountY+v].setDestroyability(false);
            undestroyableBlocks[u*undestroyableBlockAmountY+v].setHP(-1);
        }

    //Generate tank blocks so that they are to the right of simple ones
    for(int v = 1; v <= tankBlockAmountY; v++)
    {
        tankBlocks.emplace_back(600, (v+1)*(blockY + 25),sf::Color::Green);
        tankBlocks[v].setHP(3);
    }

    //Generate speed blocks so that they are to the right of the tank ones.
    for (int v = 1; v <= speedBlockAmountY; v++)
    {
        speedBlocks.emplace_back(670, (v+1)*(blockY + 25), sf::Color::Yellow);
        speedBlocks[v].setSpeedBonus(ballSpeedBonus);
    }

    //Generate bonus blocks so that they are lower than the rest.
    for(int u = 1; u <= bonusBlockAmountX; u++)
        bonusBlocks.emplace_back(u*(blockX+70) + 10, 280, sf::Color::Magenta);

    //Generate saving bottom in the bottom of window
    //savingBottom = {0, windowHeight - 20 - savingBottomHeight, windowWidth, savingBottomHeight, sf::Color::White};
    //savingBottom.setSavingBottom(true);


}

void Game::setBonuses() {
    //We generate bonuses so that they are in the center of the bonus blocks.
    //Their Color is White and defined in Bonus.h in constructor
    bonusChangeSize = BonusChangeSize (1*(blockX+70) + 10, 280);
    bonusChangeSpeed = BonusChangeSpeed (2*(blockX+70) + 10, 280);
    bonusBall = BonusBall (3*(blockX+70) + 10, 280);
    bonusSavingBottom = BonusSavingBottom (4*(blockX+70) + 10, 280);
   // bonusStickiness = BonusStickiness (5*(blockX+70) + 10, 280);

    bonuses.emplace_back(&bonusChangeSize);
    bonuses.emplace_back(&bonusChangeSpeed);
    bonuses.emplace_back(&bonusBall);
    bonuses.emplace_back(&bonusSavingBottom);

 //   bonuses.emplace_back(bonusStickiness);

}

//Helper functions for mainLoop ----------------------------------------------
void Game::checkBallBlockCollision(std::vector<Block> &blockType, std::vector<Ball> &balls, Statistics &statistics) {
    for(auto& block : blockType) {
        Collision(block, balls, statistics);
    }
}
void Game::deletingBlocks(std::vector<Block> &blockType) {
    blockType.erase(std::remove_if(begin(blockType), end(blockType), [](Block& block) {return block.getDeleted();}), end(blockType));
}
void Game::drawBricks(std::vector<Block>& blockType) {
    for(auto &block : blockType)
        window.draw(block);
}
//-----------------------------------------------------------------------------
void Game::mainLoop() {
    while(window.isOpen()){
        sf::Event event;
        while(window.pollEvent(event))
            if(event.type == sf::Event::Closed)
                window.close();
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
            window.close();
//        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
//        {
//            //Здесь добавить обработку липкости
//        }
        // CHECKING COLLISIONS------------------------------------------------
        checkBallBlockCollision(simpleBlocks, balls, statistics);
        deletingBlocks(simpleBlocks);

        checkBallBlockCollision(undestroyableBlocks, balls, statistics);
        deletingBlocks(undestroyableBlocks);

        checkBallBlockCollision(tankBlocks, balls, statistics);
        deletingBlocks(tankBlocks);

        checkBallBlockCollision(speedBlocks, balls, statistics);
        deletingBlocks(speedBlocks);

        for(int i = 0; i < bonusBlocks.size(); i++)
        {
            Collision(bonusBlocks[i], balls, statistics);
            if(bonusBlocks[i].getDeleted()) {
                std::cout << "." << std::endl;

                bonuses[i]->setBonusState(Bonus::bonusState::MOVING);
            }
        }
        deletingBlocks(bonusBlocks);
        Collision(bogey, balls);

        for(int i = 0; i < balls.size(); i++)
            for(int j = 0; j < balls.size(); j++)
                if(i!=j)
                    Collision(balls[i], balls[j]);

        for(auto& bonus : bonuses)
            Collision(bogey, *bonus);

        if(savingBottom != nullptr)
        {
            Collision(*savingBottom, balls, statistics, false);
            if(savingBottom->getDeleted())
                savingBottom = nullptr;
        }

        //--------------------------------------------------------------------------


        bogey.bogeyUpdate();
        for (auto &ball : balls)
            ball.ballUpdate(statistics);
        for(auto &bonus : bonuses)
            if(bonus->getBonusState() == Bonus::bonusState::MOVING)
                bonus->bonusUpdate();

        window.clear();

        //for (auto& bonus : bonuses) {
        for(int i = 0; i < bonuses.size(); i++ ){
            if(bonuses[i]->getBonusState() == Bonus::bonusState::RECEIVED)
            {
                bonuses[i]->effect(balls, &savingBottom, bogey);
                bonuses.erase(bonuses.begin()+i);
                std::cout << "!" << std::endl;
            }

        }
        //bonuses.erase(remove_if(begin(bonuses), end(bonuses),
      //  [](Bonus *bonus) {return  (bonus->getBonusState() == Bonus::bonusState::RECEIVED);}), end(bonuses));
        drawObjects();
    }
}

void Game::textStream() {
    std::ostringstream scoreTextStream, hpTextStream, finalPhraseStream;
    scoreTextStream << statistics.getScore();
    hpTextStream << statistics.getHP();
    scoreText.setString("Score: " + scoreTextStream.str());
    hpText.setString("HP: " + hpTextStream.str());
}

void Game::updateStats() {
    if(statistics.getScore() > 37 && statistics.getHP() != 0) {
        finalPhrase.setString("WIN");
        finalPhrase.setFillColor(sf::Color::Yellow);
        for (auto &ball : balls)
            ball.setSpeed( {0, 0} );
        window.draw(finalPhrase);
    }
    if(statistics.getHP() == 0) {
        finalPhrase.setString("GAME OVER");
        finalPhrase.setFillColor(sf::Color::Yellow);
        for (auto &ball : balls)
            ball.setSpeed( {0, 0} );
        window.draw(finalPhrase);
    }

}

void Game::drawObjects() {
    textStream();
    for(auto &ball : balls)
        window.draw(ball);
    window.draw(bogey);
    drawBricks(simpleBlocks);
    drawBricks(undestroyableBlocks);
    drawBricks(tankBlocks);
    drawBricks(speedBlocks);
    drawBricks(bonusBlocks);
    for(auto &bonus : bonuses)
    {
        window.draw(*bonus);
    }
    if(savingBottom != nullptr)
        window.draw(*savingBottom);
    window.draw(scoreText);
    window.draw(hpText);
    updateStats();
    window.display();
}

//void Game::Close() {
//    deletingBlocks(bonusBlocks);
//}













