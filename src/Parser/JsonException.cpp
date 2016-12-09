//
// Created by babiole on 18/10/16.
//

#include "Parser/JsonException.hpp"

JsonException::JsonException(const std::string &msg)
        : std::runtime_error("JsonParser : " + msg)
{}