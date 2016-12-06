//
// Created by consta_n on 9/19/16.
//

#ifndef PARSERJSON_H
#define PARSERJSON_H

#include "AParser.hpp"
#include "ConsumerParser.hpp"
#include "JsonVariant.hpp"
#include "JsonException.hpp"


class ParserJson : public ConsumerParser, public AParser
{
public:
    ParserJson(ProducterStream &);
    virtual bool parse(JsonVariant::json_pair *content);

private:
    bool key;

private:
    bool save_key(JsonVariant::json_pair* json_node,  const std::string &context, bool ret, int index);
    bool save_value(JsonVariant::json_pair* json_node,  const std::string &context, bool ret, int index);
    bool members(JsonVariant::json_pair* json_node, const std::string &context = "", int index = 0);
    bool pair(JsonVariant::json_pair* json_node, const std::string &context = "", int index = 0);
    bool value(JsonVariant::json_pair* json_node, const std::string &context = "", int index = 0);
    bool array(JsonVariant::json_pair* json_node, const std::string &context = "", int index = 0);
    bool elements(JsonVariant::json_pair* json_node, const std::string &context = "", int index = 0);
    bool object(JsonVariant::json_pair* json_node, const std::string &context = "", int index = 0);
    bool string(JsonVariant::json_pair* json_node, const std::string &context = "", int index = 0);
};

#endif //PARSERJSON_H
