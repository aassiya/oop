#include "gamefield.h"

GameField::GameField(int rows, int columns, const std::vector<int> &shipSizes) : rows(rows), columns(columns), field(rows, std::vector<CellStatus>(columns, CellStatus::UNKNOWN)), shipsManager(shipSizes)
{
    if (rows <= 0 || columns <= 0)
    {
        throw std::invalid_argument("The size of the field must be greater than zero.");
    }
    printField();
}

GameField::GameField(const GameField &other)
    : rows(other.rows), columns(other.columns), field(other.field), shipsManager(other.shipsManager) {}

GameField::GameField(GameField &&other) noexcept
    : rows(other.rows), columns(other.columns), field(std::move(other.field)), shipsManager(std::move(other.shipsManager)) {}

GameField &GameField::operator=(const GameField &other)
{
    if (this != &other)
    {
        rows = other.rows;
        columns = other.columns;
        field = other.field;
        shipsManager = other.shipsManager;
    }
    return *this;
}

GameField &GameField::operator=(GameField &&other) noexcept
{
    if (this != &other)
    {
        rows = other.rows;
        columns = other.columns;
        field = std::move(other.field);
        shipsManager = std::move(other.shipsManager);
    }
    return *this;
}

GameField::~GameField() {}

void GameField::placeShip(int shipIndex, bool isVertical, int x, int y)
{
    if (shipIndex < 0 || shipIndex >= shipsManager.getNumberOfShips())
    {
        throw std::out_of_range("Ship index out of range.");
    }
    int currentLength = shipsManager.getShipLength(shipIndex);
    for (size_t i = 0; i < currentLength; i++)
    {
        int currentX = isVertical ? x : x + i;
        int currentY = isVertical ? y + i : y;

        if (!isValidCoordinate(currentX, currentY) || field[currentY][currentX] != CellStatus::UNKNOWN)
        {
            throw std::invalid_argument("Invalid coordinates or cell already occupied.");
        }

        if (shipsAreTouching({currentX, currentY}))
        {
            throw std::invalid_argument("Current ship is touching another ship.");
        }
    }

    shipsManager.addShip(shipIndex, isVertical, x, y);
    for (size_t i = 0; i < currentLength; i++)
    {
        int currentX = isVertical ? x : x + i;
        int currentY = isVertical ? y + i : y;
    }
    printYourField();
}

void GameField::attack(const Coordinate &coord)
{
    if (!isValidCoordinate(coord.x, coord.y))
    {
        throw std::out_of_range("Coordinate out of range.");
    }

    CellStatus &cell = field[coord.y][coord.x];
    if (cell == CellStatus::UNKNOWN)
    {
        if (shipsManager.isShipAt(coord))
        {
            shipsManager.applyShipDamage(coord);
            cell = CellStatus::SHIP;
            std::cout << "Hit the coordinate " << coord << "\n";
        }
        else
        {
            cell = CellStatus::EMPTY;
            std::cout << "Past the coordinate " << coord << "\n";
        }
    }
    else if (cell == CellStatus::EMPTY)
    {
        std::cout << "The coordinate " << coord << " is already known\n";
    }
    else
    {
        SegmentState currentState = shipsManager.getSegmentState({coord.x, coord.y});
        if (currentState == SegmentState::DAMAGED)
        {
            shipsManager.applyShipDamage(coord);
            std::cout << "Ship segment at coordinate " << coord << " destroyed\n";
        }
        else if (currentState == SegmentState::DESTROYED)
        {
            shipsManager.applyShipDamage(coord);
            std::cout << "The ship at coordinate " << coord << " is already known\n";
        }
    }
    printField();
}

CellStatus GameField::getCellStatus(int x, int y) const
{
    if (!isValidCoordinate(x, y))
    {
        throw std::out_of_range("Coordinate out of range.");
    }
    return field[y][x];
}

void GameField::printField() const
{
    for (int y = 0; y < rows; y++)
    {
        for (int x = 0; x < columns; x++)
        {
            if (shipsManager.isShipAt({x, y}))
            {
                switch (shipsManager.getSegmentState({x, y}))
                {
                case SegmentState::UNHARMED:
                    std::cout << ". ";
                    break;
                case SegmentState::DAMAGED:
                    std::cout << "* ";
                    break;
                case SegmentState::DESTROYED:
                    std::cout << "x ";
                    break;

                default:
                    break;
                }
            }
            else
            {
                switch (field[y][x])
                {
                case CellStatus::UNKNOWN:
                    std::cout << ". ";
                    break;
                case CellStatus::EMPTY:
                    std::cout << "o ";
                    break;
                }
            }
        }
        std::cout << "\n";
    }
    std::cout << "\n";
}

void GameField::printYourField() const
{
    std::cout << "Your Field:\n";
    for (int y = 0; y < rows; y++)
    {
        for (int x = 0; x < columns; x++)
        {
            if (shipsManager.isShipAt({x, y}))
            {
                switch (shipsManager.getSegmentState({x, y}))
                {
                case SegmentState::UNHARMED:
                    std::cout << "~ ";
                    break;
                case SegmentState::DAMAGED:
                    std::cout << "* ";
                    break;
                case SegmentState::DESTROYED:
                    std::cout << "x ";
                    break;
                default:
                    std::cout << "? ";
                    break;
                }
            }
            else
            {
                std::cout << ". ";
            }
        }
        std::cout << "\n";
    }
    std::cout << "\n";
}

bool GameField::isValidCoordinate(int x, int y) const
{
    if (x >= 0 && x < columns && y >= 0 && y < rows)
    {
        return true;
    }
    return false;
}

bool GameField::shipsAreTouching(const Coordinate &coord) const
{
    for (int dx = -1; dx <= 1; dx++)
    {
        for (int dy = -1; dy <= 1; dy++)
        {
            if (dx == 0 && dy == 0)
            {
                continue;
            }
            int current_x = coord.x + dx;
            int current_y = coord.y + dy;
            if (isValidCoordinate(current_x, current_y))
            {
                if (shipsManager.isShipAt({current_x, current_y}))
                {
                    return true;
                }
            }
        }
    }
    return false;
}