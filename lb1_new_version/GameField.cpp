#include "GameField.h"

std::ostream &operator<<(std::ostream &os, const CellState &state)
{
    switch (state)
    {
    case CellState::EMPTY:
        os << "Empty";
        break;
    case CellState::SHIP:
        os << "Ship";
        break;
    case CellState::UNKNOWN:
        os << "Unknown";
        break;
        return os;
    }
    return os;
}

GameField::GameField(int rows, int columns) : rows(rows), columns(columns), field(rows, std::vector<Cell>(columns)) {}

GameField::GameField(const GameField &other) : rows(other.rows), columns(other.columns), field(other.field) {}

GameField::GameField(GameField &&other) : rows(other.rows), columns(other.columns), field(std::move(other.field))
{
    other.rows = 0;
    other.columns = 0;
}

GameField::~GameField() {}

GameField &GameField::operator=(const GameField &other)
{
    if (this != &other)
    {
        rows = other.rows;
        columns = other.columns;
        field.resize(other.field.size());
        for (size_t i = 0; i < field.size(); ++i)
        {
            field[i].resize(other.field[i].size());
            for (size_t j = 0; j < field[i].size(); ++j)
            {
                field[i][j] = other.field[i][j];
            }
        }
    }
    return *this;
}

GameField &GameField::operator=(GameField &&other)
{
    if (this != &other)
    {
        rows = other.rows;
        columns = other.columns;
        field = std::move(other.field);
    }
    return *this;
}

bool GameField::isValidCoordinate(int x, int y) const
{
    if (x >= 0 && x < columns && y >= 0 && y < rows)
    {
        return true;
    }
    return false;
}

bool GameField::shipsAreTouching(Ship *ship, bool isVertical, int x, int y) const
{
    if (isVertical)
    {
        for (int i = y; i < y + ship->getLength(); i++)
        {
            for (int dx = -1; dx <= 1; dx++)
            {
                for (int dy = -1; dy <= 1; dy++)
                {
                    if (dx == 0 && dy == 0)
                    {
                        continue;
                    }
                    int current_x = x + dx;
                    int current_y = i + dy;
                    if (isValidCoordinate(current_x, current_y))
                    {
                        if (field[current_y][current_x].isShip())
                        {
                            return true;
                        }
                    }
                }
            }
        }
    }
    else
    {
        for (int i = x; i < x + ship->getLength(); i++)
        {
            for (int dx = -1; dx <= 1; dx++)
            {
                for (int dy = -1; dy <= 1; dy++)
                {
                    if (dx == 0 && dy == 0)
                    {
                        continue;
                    }
                    int current_x = i + dx;
                    int current_y = y + dy;
                    if (isValidCoordinate(current_x, current_y))
                    {
                        if (field[current_y][current_x].isShip())
                        {
                            return true;
                        }
                    }
                }
            }
        }
    }
    return false;
}

int GameField::getRows() const
{
    return rows;
}

int GameField::getColumns() const
{
    return columns;
}

bool GameField::shipInCell(int x, int y) const
{
    // if (!isValidCoordinate(x, y)) {
    // обработка ошибки
    // }
    return field[y][x].isShip();
}

CellState GameField::getCellState(int x, int y) const
{
    // if (!isValidCoordinate(x, y)) {

    // }
    return field[y][x].getState();
}
SegmentState GameField::getShipSegmentState(int x, int y) const
{
    // if (!isValidCoordinate(x, y)) {

    // }
    return field[y][x].getShipSegmentState();
}

void GameField::placeShip(Ship *ship, bool isVertical, int x, int y)
{
    // допилить!
    // if (ship == nullptr)
    // {
    //     throw std::invalid_argument("Ship pointer is null");
    // }
    // if (shipsAreTouching(ship, isVertical, x, y))
    // {
    //     throw ShipCollisionException();
    // }

    if (isVertical)
    {
        if (!isValidCoordinate(x, y + ship->getLength() - 1))
        {
            throw std::out_of_range("The ship's coordinates are incorrect.");
        }
        for (int i = y; i < y + ship->getLength(); i++)
        {
            field[i][x].setShipSegment(ship, i - y);
        }
    }
    else
    {
        if (!isValidCoordinate(x + ship->getLength() - 1, y))
        {
            throw std::out_of_range("The ship's coordinates are incorrect.");
        }
        for (int i = x; i < x + ship->getLength(); i++)
        {
            field[y][i].setShipSegment(ship, i - x);
        }
    }
}

void GameField::attackCell(int x, int y)
{
    // try
    // {
    // if (!isValidCoordinate(x, y))
    // {
    //    throw OutOfBoundsAttackException();
    // }

    if (shipInCell(x, y))
    {
        field[y][x].attackCell();
        field[y][x].setState(CellState::SHIP);
    }
    else
    {
        field[y][x].setState(CellState::EMPTY);
    }
    // }
    // catch (const OutOfBoundsAttackException &e)
    // {
    //     std::cerr << e.what() << std::endl;
    // }
}

void GameField::printField() const
{
    for (int y = 0; y < rows; y++)
    {
        for (int x = 0; x < columns; x++)
        {
            CellState cellState = getCellState(x, y);
            if (cellState == CellState::UNKNOWN)
            {
                std::cout << "[ ]";
            }
            else if (cellState == CellState::EMPTY)
            {
                std::cout << "[-]";
            }
            else
            {
                SegmentState segmentState = getShipSegmentState(x, y);
                if (segmentState == SegmentState::UNHARMED)
                {
                    std::cout << "[0]";
                }
                else if (segmentState == SegmentState::DAMAGED)
                {
                    std::cout << "[.]";
                }
                else
                {
                    std::cout << "[x]";
                }
            }
        }
        std::cout << "\n";
    }
    std::cout << "\n";
}

GameField::Cell::Cell() : state_(CellState::UNKNOWN), ship_(nullptr), segmentIndex(-1)
{
}

GameField::Cell::~Cell() {}

bool GameField::Cell::isShip() const
{
    return ship_ != nullptr;
}

void GameField::Cell::setState(CellState state)
{
    state_ = state;
}

CellState GameField::Cell::getState() const
{
    return state_;
}

void GameField::Cell::setShipSegment(Ship *ship, int index)
{
    state_ = CellState::SHIP;
    ship_ = ship;
    segmentIndex = index;
}

SegmentState GameField::Cell::getShipSegmentState() const
{
    if (ship_ == nullptr)
    {
        return SegmentState::UNHARMED;
    }
    return ship_->getSegmentState(segmentIndex);
}

void GameField::Cell::attackCell()
{
    if (ship_ != nullptr)
    {
        ship_->applySegmentDamage(segmentIndex);
    }
}

Ship *GameField::Cell::getShip() const
{
    return ship_;
}
