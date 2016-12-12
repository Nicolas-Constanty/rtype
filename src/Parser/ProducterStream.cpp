//
// Created by consta_n on 9/19/16.
//

#include <iostream>
#include <fstream>
#include <stdexcept>
#include "Parser/ProducterStream.hpp"

ProducterStream::ProducterStream() {
    _ifs = new std::ifstream();
}

ProducterStream::~ProducterStream() {
    if (_ifs->is_open())
        _ifs->close();
    delete _ifs;
}

std::string ProducterStream::nextString() {
    char _buff[BUFF_SIZE + 1] = {0};
    _stream->read(_buff, BUFF_SIZE);
    std::string res = std::string(_buff);
    if (res.length() == 0)
    {
        if (_ifs->is_open())
            _ifs->close();
        throw std::runtime_error("Fail nextString");
    }
    return res;
}

bool ProducterStream::loadFile(const char *path)
{
    if (_ifs->is_open())
        _ifs->close();
    _ifs->open (path);
    _stream = _ifs;
    return (_ifs->is_open());
}

bool ProducterStream::loadStdin()
{
    if (_ifs->is_open())
        _ifs->close();
    _stream = &std::cin;
    return (_ifs->is_open());
}


