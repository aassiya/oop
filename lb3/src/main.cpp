#include <iostream>
#include <limits>
#include <sstream>

#include "Ship.hpp"
#include "ShipsManager.hpp"
#include "GameField.hpp"
#include "Ability.hpp"
#include "AbilityManager.hpp"
#include "NoAbilitiesError.hpp"
#include "GameController.hpp"

int main()
{
    GameController gameController;
    gameController.startNewGame();
    return 0;
}