#include "gamefield.h"
#include "shipsmanager.h"

int main()
{
    ShipsManager manager({3, 2});
    GameField field(10, 10);

    // Создаем корабль через конструктор
    Ship ship1(4, false);

    // Добавляем корабли в менеджер
    manager.addShip(ship1);

    // Получаем указатели на корабли
    Ship *shipPtr0 = manager.getShip(0);
    Ship *shipPtr1 = manager.getShip(1);
    Ship *shipPtr2 = manager.getShip(2);

    // Размещаем корабли на поле
    field.placeShip(shipPtr0, false, 1, 8);
    field.placeShip(shipPtr1, true, 3, 2);
    field.placeShip(shipPtr2, false, 6, 4);
    std::cout << field.getCellState(3, 2);

    // Печатаем поле
    field.printField();

    // Атакуем клетки
    field.attackCell(3, 2);
    field.attackCell(3, 2);
    field.printField();

    field.attackCell(6, 4);
    field.attackCell(5, 4);
    field.printField();
    return 0;
}