//
// Created by consta_n on 9/19/16.
//

#ifndef CONSUMERPARSER_H
#define CONSUMERPARSER_H

#include <functional>
#include <map>
#include <vector>
#include "ProducterStream.hpp"
#include <iostream>
class ConsumerParser {
protected:
    ProducterStream &_ps;
    std::string     _buffer;
    std::map<std::string, std::string>      _capture;
    std::string                             _tag;
    bool repeater(const std::function<bool()> &func, char c);
    std::string _ignore;
    char _comment;
protected:
    ConsumerParser(ProducterStream &);
    bool readText(char *text);
    bool readEOF();
    bool readUntil(char c);
    bool readUntilEOF();
    bool readInteger();
    //Id := [a .. z] | [A .. Z] | '_' [[a .. z] | [A .. Z] | [0 .. 9] | '_']*
    bool readIdentifier();
    //Value := [[a .. z] | [A .. Z] | [0 .. 9] | '_']*
    bool readValue();

protected:
    inline bool beginCapture(std::string tag)
    {
        if (readEOF())
            return (false);
        _tag = tag;
        _capture[_tag] = "";
        return (true);
    }

    inline bool endCapture(std::string tag, std::string& out)
    {
        if (_capture.find(tag) == _capture.end())
            return (false);
        out = _capture[tag];
        _tag.clear();
        _tag = "";
        return (true);
    }

    inline bool flush()
    {
        _buffer.clear();
        return (true);
    }

    inline bool peekChar(char c)
    {
        if (_buffer.empty())
        {
            try {
                _buffer += _ps.nextString();
            }
            catch (std::runtime_error e)
            {
                return (false);
            }
        }
        return (_buffer[0] == c);
    }

    inline void ignore_char(char c)
    {
        int i = 0;

        if (peekChar(c))
          return;
        while (_ignore[i]) {
            if (_buffer[0] == _ignore[i])
            {
                _buffer = _buffer.substr(1);
                if (peekChar(c))
                    return;
                i = -1;
            }
            ++i;
        }
    }

    inline bool readChar(char c)
    {
        if (_buffer[0] == _comment)
        {
            _buffer = _buffer.substr(1);
            std::string tmp = _tag;
            _tag = "";
            bool ret = readUntil('\n');
            _tag = tmp;
            return (ret);
        }
        ignore_char(c);
        if (peekChar(c))
        {
            if (!_tag.empty())
                _capture[_tag] += _buffer[0];
            _buffer = _buffer.substr(1);
            return (true);
        }
        return (false);
    }

    inline bool readRange(char begin, char end)
    {
        while (begin != end +1)
        {
            if (readChar(begin))
                return (true);
            ++begin;
        }
        return  (false);
    }
};


#endif //CONSUMERPARSER_H
