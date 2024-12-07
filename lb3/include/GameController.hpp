#ifndef GAME_CONTROLLER_HPP
#define GAME_CONTROLLER_HPP

#include <iostream>
#include <limits>
#include <sstream>

#include "Ship.hpp"
#include "ShipsManager.hpp"
#include "GameField.hpp"
#include "Ability.hpp"
#include "AbilityManager.hpp"
#include "NoAbilitiesError.hpp"
#include "GameState.hpp"

class GameController
{
public:
    GameController();
    ~GameController();

    void startNewGame();
    void resetEnemyState();
    void resetPlayerState();
    int playRound();
    int playerTurn(int enemyShipCount);
    bool playerAttack();
    int enemyTurn(int playerShipCount);

    void save();
    void load();

private:
    GameField *enemyGameField;
    ShipsManager *enemyShipsManager;
    GameField *playerGameField;
    ShipsManager *playerShipsManager;
    AbilityManager *playerAbilityManager;
    GameState gameState;
};

#endif