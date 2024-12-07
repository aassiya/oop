#ifndef FILE_ERROR_HPP
#define FILE_ERROR_HPP

#include "structures.hpp"

class FileError : public std::runtime_error
{
public:
    FileError(const std::string &msg) : std::runtime_error(msg) {}
};

#endif