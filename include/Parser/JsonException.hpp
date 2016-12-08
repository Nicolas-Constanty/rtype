//
// Created by babiole on 18/10/16.
//

#ifndef PAMELA_JSONEXCEPTION_HPP
#define PAMELA_JSONEXCEPTION_HPP


#include <stdexcept>
#include <sstream>

class JsonException : public std::runtime_error
{
public:
    JsonException(const std::string &msg);
};

#endif //PAMELA_JSONEXCEPTION_HPP
