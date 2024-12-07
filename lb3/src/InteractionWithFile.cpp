#include "InteractionWithFile.hpp"

InteractionWithFile::InteractionWithFile(const std::string &filename) : filename(filename) {}

InteractionWithFile::~InteractionWithFile()
{
    outfile.close();
    infile.close();
}

std::ofstream InteractionWithFile::open_for_save()
{
    std::ofstream outfile(filename);
    if (!outfile.is_open())
    {
        throw FileError("Unable to open file for reading\n");
    }
    return outfile;
}

void InteractionWithFile::save(std::ofstream &outfile, const GameState &gameState)
{
    outfile << gameState;
}

void InteractionWithFile::close_saving(std::ofstream &outfile)
{
    outfile.close();
}

std::ifstream InteractionWithFile::open_for_writing()
{
    std::ifstream infile(filename);
    if (!infile.is_open())
    {
        throw FileError("Unable to open file for writing\n");
    }
    return infile;
}

void InteractionWithFile::write(std::ifstream &infile, GameState &game)
{
    std::string json_string((std::istreambuf_iterator<char>(infile)), std::istreambuf_iterator<char>());
    json j = json::parse(json_string);
    infile >> game;
}

void InteractionWithFile::close_writing(std::ifstream &infile)
{
    infile.close();
}
