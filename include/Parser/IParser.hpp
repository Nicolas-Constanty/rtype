#ifndef IPARSER_H
#define IPARSER_H

#include <map>
#include <boost/variant.hpp>
#include "JsonVariant.hpp"

class IParser
{
  public:
    virtual bool parse(JsonVariant::json_pair *content) = 0;
};


#endif //IPARSER_H
