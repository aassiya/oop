#include "GameField.hpp"

GameField::GameField() {}

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
    if (isValidCoordinate(x, y))
    {
        return field[y][x].isShip();
    }
    return false;
}

CellState GameField::getCellState(int x, int y) const
{
    if (isValidCoordinate(x, y))
    {
        return field[y][x].getState();
    }
    return CellState();
}
SegmentState GameField::getShipSegmentState(int x, int y) const
{
    if (isValidCoordinate(x, y))
    {
        return field[y][x].getShipSegmentState();
    }
    return SegmentState();
}

void GameField::placeShip(Ship *ship, bool isVertical, int x, int y)
{
    if (shipsAreTouching(ship, isVertical, x, y))
    {
        throw PlaceShipError("Error: Ship is placed too close to another ship or intersecting with another ship\n");
    }

    if (isVertical)
    {
        if (!isValidCoordinate(x, y) || !isValidCoordinate(x, y + ship->getLength() - 1))
        {
            throw PlaceShipError("Error: Incorrect coordinates\n");
        }
        for (int i = y; i < y + ship->getLength(); i++)
        {
            field[i][x].setShipSegment(ship, i - y);
        }
    }
    else
    {
        if (!isValidCoordinate(x, y) || !isValidCoordinate(x + ship->getLength() - 1, y))
        {
            throw PlaceShipError("Error: Incorrect coordinates\n");
        }
        for (int i = x; i < x + ship->getLength(); i++)
        {
            field[y][i].setShipSegment(ship, i - x);
        }
    }
}

void GameField::placeShipsRandomly(std::vector<int> ships)
{
    for (int size : ships)
    {
        bool placed = false;
        while (!placed)
        {
            int x = std::rand() % getColumns();
            int y = std::rand() % getRows();
            bool isVertical = std::rand() % 2 == 0;

            Ship *ship = new Ship(size, isVertical);

            try
            {
                placeShip(ship, isVertical, x, y);
                placed = true;
            }
            catch (const PlaceShipError &e)
            {
                delete ship;
            }
        }
    }
}

bool GameField::attackCell(int x, int y, int damage)
{
    if (!isValidCoordinate(x, y))
    {
        throw AttackCellError("Error: Incorrect coordinates\n");
    }

    if (shipInCell(x, y))
    {
        field[y][x].attackCell(damage);
        field[y][x].setState(CellState::SHIP);
        if (field[y][x].getShip()->isDestroyed())
        {
            return true;
        }
    }
    else
    {
        field[y][x].setState(CellState::EMPTY);
    }
    return false;
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

void GameField::printEnemyField() const
{
    for (int y = 0; y < rows; y++)
    {
        for (int x = 0; x < columns; x++)
        {
            if (field[y][x].getState() == CellState::UNKNOWN)
            {
                std::cout << "[ ]";
            }
            else if (field[y][x].getState() == CellState::EMPTY)
            {
                std::cout << "[-]";
            }
            else
            {
                if (field[y][x].getShipSegmentState() == SegmentState::DAMAGED)
                {
                    std::cout << "[.]";
                }
                else if (field[y][x].getShipSegmentState() == SegmentState::DESTROYED)
                {
                    std::cout << "[x]";
                }
                else
                {
                    std::cout << "[ ]";
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

int GameField::Cell::getSegmentIndex() const
{
    return segmentIndex;
}

SegmentState GameField::Cell::getShipSegmentState() const
{
    if (ship_ == nullptr)
    {
        return SegmentState::UNHARMED;
    }
    return ship_->getSegmentState(segmentIndex);
}

void GameField::Cell::attackCell(int damage)
{
    if (ship_ != nullptr)
    {
        ship_->applySegmentDamage(segmentIndex, damage);
    }
}

Ship *GameField::Cell::getShip() const
{
    return ship_;
}

json GameField::saveToJson() const
{
    json j;

    j["rows"] = rows;
    j["columns"] = columns;

    j["field"] = json::array();
    for (int y = 0; y < rows; ++y)
    {
        json row = json::array();
        for (int x = 0; x < columns; ++x)
        {
            json cell;
            const Cell &currentCell = field[y][x];

            cell["state"] = static_cast<int>(currentCell.getState());

            if (currentCell.isShip())
            {
                cell["has_ship"] = true;
                cell["segment_index"] = currentCell.getSegmentIndex();

                Ship *ship = currentCell.getShip();
                cell["ship"] = {
                    {"length", ship->getLength()},
                    {"is_vertical", ship->getOrientation()},
                    {"segments", json::array()}};

                for (int i = 0; i < ship->getLength(); ++i)
                {
                    cell["ship"]["segments"].push_back(static_cast<int>(ship->getSegmentState(i)));
                }
            }
            else
            {
                cell["has_ship"] = false;
            }

            row.push_back(cell);
        }
        j["field"].push_back(row);
    }

    return j;
}

void GameField::loadFromJson(const json &j)
{
    rows = j["rows"];
    columns = j["columns"];
    field.resize(rows, std::vector<Cell>(columns));

    for (int y = 0; y < rows; ++y)
    {
        for (int x = 0; x < columns; ++x)
        {
            const json &cell = j["field"][y][x];
            field[y][x].setState(static_cast<CellState>(cell["state"].get<int>()));

            if (cell["has_ship"].get<bool>())
            {
                json shipData = cell["ship"];
                Ship *ship = new Ship(
                    shipData["length"].get<int>(),
                    shipData["is_vertical"].get<bool>());

                const auto &segments = shipData["segments"];
                for (int i = 0; i < ship->getLength(); ++i)
                {
                    SegmentState segmentState = static_cast<SegmentState>(segments[i].get<int>());
                    if (segmentState == SegmentState::DAMAGED)
                    {
                        ship->applySegmentDamage(i, 1);
                    }
                    else if (segmentState == SegmentState::DESTROYED)
                    {
                        ship->applySegmentDamage(i, 2);
                    }
                }

                field[y][x].setShipSegment(ship, cell["segment_index"].get<int>());
            }
        }
    }
}

std::pair<int, int> GameField::fromJsonSize(const json &j)
{
    if (!j.contains("rows") || !j.contains("columns"))
    {
        throw std::invalid_argument("JSON does not contain field dimensions.");
    }
    int rows = j["rows"].get<int>();
    int columns = j["columns"].get<int>();
    return {rows, columns};
}