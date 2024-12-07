#include "GameController.hpp"

GameController::GameController() : gameState("game.json") {}

GameController::~GameController()
{
    delete enemyGameField;
    delete enemyShipsManager;
    delete playerGameField;
    delete playerShipsManager;
    delete playerAbilityManager;
}
void GameController::startNewGame()
{
    bool newGame = true;
    while (true)
    {
        if (newGame)
        {
            std::cout << "Do you want to download the previous game? (y/n): ";
            char choice;
            std::cin >> choice;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            if (choice == 'y' || choice == 'Y')
            {
                load();
                std::cout << "Previous game successfully downloaded!\n";
                enemyGameField->printEnemyField();
                playerGameField->printField();
            }
            else
            {
                std::cout << "Starting a new game!" << std::endl;
                resetPlayerState();
                resetEnemyState();
            }
        }
        else
        {
            std::cout << "Starting a new round!" << std::endl;
            resetEnemyState();
        }
        int gameWon = playRound();
        if (gameWon == 1)
        {
            std::cout << "Congratulations, you won this round! Starting the next round..." << std::endl;
            newGame = false;
        }
        else if (gameWon == 0)
        {
            std::cout << "You lost the game. Would you like to start a new game? (y/n): ";
            char choice;
            std::cin >> choice;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            if (choice == 'y' || choice == 'Y')
            {
                newGame = true;
            }
            else
            {
                std::cout << "Exiting the game. Thank you for playing!" << std::endl;
                break;
            }
        }
        else
        {
            break;
        }
    }
}

void GameController::resetEnemyState()
{
    int rows = 5, columns = 5;
    std::vector<int> enemyShips = {1, 1, 2, 3};
    enemyGameField = new GameField(rows, columns);
    enemyShipsManager = new ShipsManager(enemyShips);
    enemyGameField->placeShipsRandomly(enemyShips);
}

void GameController::resetPlayerState()
{
    int rows = 5, columns = 5;
    std::vector<int> ships = {1, 1, 2, 3};
    playerGameField = new GameField(rows, columns);
    playerShipsManager = new ShipsManager(ships);
    playerAbilityManager = new AbilityManager();

    playerGameField->placeShipsRandomly(ships);
    playerGameField->printField();
}

int GameController::playRound()
{
    bool playerDestroyed = false, enemyDestroyed = false, earlyBreak = false;
    bool turn = true;
    int enemyShipCount = enemyShipsManager->getNumberOfShips(), playerShipCount = playerShipsManager->getNumberOfShips();
    while (!playerDestroyed && !enemyDestroyed && !earlyBreak)
    {
        if (turn)
        {
            enemyShipCount = playerTurn(enemyShipCount);
            turn = false;
        }
        else
        {
            playerShipCount = enemyTurn(playerShipCount);
            turn = true;
        }
        if (playerShipCount == 0)
        {
            playerDestroyed = true;
        }
        if (enemyShipCount == 0)
        {
            enemyDestroyed = true;
        }
        if (enemyShipCount == -1)
        {
            earlyBreak = true;
        }
    }
    if (earlyBreak)
    {
        return -1;
    }
    else if (enemyDestroyed)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int GameController::playerTurn(int enemyShipCount)
{
    std::cout << "Your turn: \nEnter '1' to use a special ability, '0' to attack\n";
    std::cout << "Enter 'end' to finish the game, enter 'save' to save the game, enter 'load' to load the game\n";
    bool turn = true;
    while (turn)
    {
        std::string input;
        std::getline(std::cin, input);
        if (input == "1")
        {
            AbilityStatus abilityStatus;
            try
            {
                auto [isDestroyed, newAbilityStatus] = playerAbilityManager->useAbility(*enemyGameField);
                abilityStatus = newAbilityStatus;
                std::cout << "Using ability result: " << abilityStatus << std::endl;
                if (isDestroyed)
                {
                    std::cout << "You have received a new ability!\n";
                    playerAbilityManager->shipWasDestroyed();
                    enemyShipCount--;
                }
            }
            catch (NoAbilitiesError &e)
            {
                std::cout << e.what() << "Try again"
                          << std::endl;
                continue;
            }

            if (abilityStatus != AbilityStatus::DESTROYED && abilityStatus != AbilityStatus::NOT_DESTROYED)
            {
                enemyGameField->printEnemyField();
                bool attacked = false;
                while (!attacked)
                {
                    try
                    {
                        bool attackResult = playerAttack();
                        if (attackResult)
                        {
                            enemyShipCount--;
                        }
                        attacked = true;
                    }
                    catch (AttackCellError &e)
                    {
                        std::cout << e.what() << "Try again\n"
                                  << std::endl;
                    }
                }
            }
            turn = false;
        }
        else if (input == "0")
        {
            bool attacked = false;
            while (!attacked)
            {
                try
                {
                    if (playerAttack())
                    {
                        enemyShipCount--;
                    }
                    attacked = true;
                }
                catch (AttackCellError &e)
                {
                    std::cout << e.what() << "Try again\n"
                              << std::endl;
                }
            }
            turn = false;
        }
        else if (input == "end")
        {
            std::cout << "The game ended early\n";
            return -1;
        }
        else if (input == "save")
        {
            save();
            std::cout << "The game has been saved successfully\n";
        } else if (input == "load") {
            load();
            std::cout << "The game has been loaded successfully\n";
            enemyGameField->printEnemyField();
            playerGameField->printField();
        }
        else
        {
            std::cout << "Error: Invalid input, try again" << std::endl;
            continue;
        }
    }
    enemyGameField->printEnemyField();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return enemyShipCount;
}

bool GameController::playerAttack()
{
    int x, y;
    std::cout << "Enter coordinates to attack (x y):" << std::endl;
    std::cin >> x >> y;
    while (enemyGameField->getCellState(x, y) == CellState::EMPTY || (enemyGameField->getCellState(x, y) == CellState::SHIP && enemyGameField->getShipSegmentState(x, y) == SegmentState::DESTROYED))
    {
        std::cout << "Enter new coordinates to attack (x y):" << std::endl;
        std::cin >> x >> y;
    }
    bool attackResult = enemyGameField->attackCell(x, y, 1);
    if (attackResult)
    {
        std::cout << "You have received a new ability!\n";
        playerAbilityManager->shipWasDestroyed();
    }
    return attackResult;
}

int GameController::enemyTurn(int playerShipCount)
{
    std::srand(static_cast<unsigned>(std::time(nullptr)));
    int x = std::rand() % enemyGameField->getColumns();
    int y = std::rand() % enemyGameField->getRows();
    while (playerGameField->getCellState(x, y) == CellState::EMPTY || (playerGameField->getCellState(x, y) == CellState::SHIP && playerGameField->getShipSegmentState(x, y) == SegmentState::DESTROYED))
    {
        x = std::rand() % enemyGameField->getColumns();
        y = std::rand() % enemyGameField->getRows();
    }
    if (playerGameField->attackCell(x, y, 1))
    {
        playerShipCount--;
    }
    std::cout << "Your field after enemy attack: \n";
    playerGameField->printField();
    return playerShipCount;
}

void GameController::save()
{
    gameState.save(playerGameField, enemyGameField, playerShipsManager, enemyShipsManager, playerAbilityManager);
}

void GameController::load()
{
    gameState.load(&playerGameField, &enemyGameField, &playerShipsManager, &enemyShipsManager, &playerAbilityManager);
}