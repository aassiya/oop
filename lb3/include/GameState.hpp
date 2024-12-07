#ifndef GAME_STATE_HPP
#define GAME_STATE_HPP

#include <string>
#include <iostream>
#include <fstream>

#include "GameField.hpp"
#include "ShipsManager.hpp"
#include "AbilityManager.hpp"
#include "InteractionWithFile.hpp"

#include <json.hpp>
using json = nlohmann::json;

class GameState
{
public:
    GameState(std::string filename);
    
    void save(GameField *playerField, GameField *enemyField, ShipsManager *playerShipsManager, ShipsManager *enemyShipsManager, AbilityManager *playerAbilityManager);
    void load(GameField **playerField, GameField **enemyField, ShipsManager **playerShipsManager, ShipsManager **enemyShipsManager, AbilityManager **playerAbilityManager);
    
    friend std::ostream &operator<<(std::ostream &os, const GameState &state);
    friend std::istream &operator>>(std::istream &is, GameState &state);

private :
    std::string filename;
    json saveGame;
    GameField *playerField;
    GameField *enemyField;
    ShipsManager *playerShipsManager;
    ShipsManager *enemyShipsManager;
    AbilityManager *playerAbilityManager;
    std::ofstream outfile;
    std::ifstream infile;
};

#endif