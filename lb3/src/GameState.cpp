#include "GameState.hpp"

GameState::GameState(std::string filename) : filename(filename) {}

void GameState::save(GameField *playerField, GameField *enemyField, ShipsManager *playerShipsManager, ShipsManager *enemyShipsManager, AbilityManager *playerAbilityManager)
{
    this->playerField = playerField;
    this->enemyField = enemyField;
    this->playerShipsManager = playerShipsManager;
    this->enemyShipsManager = enemyShipsManager;
    this->playerAbilityManager = playerAbilityManager;
    InteractionWithFile saver(filename);
    outfile = saver.open_for_save();
    saver.save(outfile, *this);
    saver.close_saving(outfile);
}

void GameState::load(GameField **playerField, GameField **enemyField, ShipsManager **playerShipsManager, ShipsManager **enemyShipsManager, AbilityManager **playerAbilityManager)
{
    InteractionWithFile writer(filename);
    infile = writer.open_for_writing();
    writer.write(infile, *this);
    *playerField = this->playerField;
    *enemyField = this->enemyField;
    *playerShipsManager = this->playerShipsManager;
    *enemyShipsManager = this->enemyShipsManager;
    *playerAbilityManager = this->playerAbilityManager;
    writer.close_writing(infile);
}

std::ostream &operator<<(std::ostream &os, const GameState &state)
{
    json j;
    j["player_field"] = state.playerField->saveToJson();
    j["enemy_field"] = state.enemyField->saveToJson();
    j["player_ships_manager"] = state.playerShipsManager->saveToJson();
    j["enemy_ships_manager"] = state.enemyShipsManager->saveToJson();
    j["player_ability_manager"] = state.playerAbilityManager->saveToJson();
    os << j.dump(4);
    return os;
}

std::istream &operator>>(std::istream &is, GameState &state)
{
    std::ifstream infile(state.filename);
    std::string json_string((std::istreambuf_iterator<char>(infile)), std::istreambuf_iterator<char>());
    json j = json::parse(json_string);
    std::pair<int, int> size = state.playerField->fromJsonSize(j["player_field"]);
    state.playerShipsManager = state.playerShipsManager->loadFromJson(j["player_ships_manager"]);
    state.enemyShipsManager = state.enemyShipsManager->loadFromJson(j["enemy_ships_manager"]);
    state.playerField = new GameField(size.first, size.second); // size.first = строки, size.second = столбцы
    state.enemyField = new GameField(size.first, size.second);
    state.playerField->loadFromJson(j["player_field"]);
    state.enemyField->loadFromJson(j["enemy_field"]);
    state.playerAbilityManager = new AbilityManager();
    state.playerAbilityManager->loadFromJson(j["player_ability_manager"], *(state.enemyField));

    return is;
}
