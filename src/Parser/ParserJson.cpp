//
// Created by consta_n on 9/19/16.
//

#include "Parser/ParserJson.hpp"

ParserJson::ParserJson(ProducterStream &ps) : ConsumerParser(ps)
{
    key = false;
}

bool ParserJson::object(JsonVariant::json_pair* json_node, const std::string &context,
                        int index)
{
    return (readChar('{') &&
            repeater([this, json_node, context, index]{
                return (members(json_node, context, index));
            }, '?') &&
            readChar('}'));
}

bool ParserJson::members(JsonVariant::json_pair* json_node, const std::string &context,
                         int index)
{
    return (pair(json_node, context, index) &&
            repeater([this, json_node, context, index] () {
                return (readChar(',') && pair(json_node, context, index));
            }, '*'));
}

bool ParserJson::save_key(JsonVariant::json_pair* json_node,  const std::string &context, bool ret, int index)
{
    beginCapture("key");
    ret = (ret && ConsumerParser::readValue());
    endCapture("key", _tmp_data);
    if (!context.empty())
    {
        JsonVariant::json_array *&a = boost::get<JsonVariant::json_array *&>(
                (*json_node)[context].getValue());
        if (!a)
            a = new std::vector<JsonVariant::json_pair *>();
        if (a->size() >= index)
        {
            JsonVariant::json_pair *p = new JsonVariant::json_pair();
            a->push_back(p);
        }
    }
    return (ret);
}

bool ParserJson::save_value(JsonVariant::json_pair* json_node,  const std::string &context, bool ret, int index)
{
    std::string val;
    beginCapture("value");
    ret = (ret && ConsumerParser::readValue());
    endCapture("value", val);
    if (!context.empty())
    {
        JsonVariant::json_array *a = boost::get<JsonVariant::json_array *>(
                (*json_node)[context].getValue());
        if (a)
        {
            JsonVariant::json_pair *p = (*a)[index];
            (*p)[_tmp_data].getValue() = val;
        }
        else
            throw JsonException("Invalid array");
    }
    return (ret);
}

bool ParserJson::string(JsonVariant::json_pair* json_node, const std::string &context,
                        int index)
{
    bool ret = readChar('"');
    if (key)
        ret = save_key(json_node, context, ret, index);
    else
        ret = save_value(json_node, context, ret, index);
    return (ret && readChar('"'));
}

bool ParserJson::pair(JsonVariant::json_pair* json_node, const std::string &context,
                      int index)
{
    bool ret;
    key = true;
    ret = value(json_node, context);
    key = false;
    return (ret && readChar(':') && value(json_node, context, index));
}

bool ParserJson::value(JsonVariant::json_pair* json_node, const std::string &context,
                       int index)
{
    return (object(json_node, context, index)||
            array(json_node, context, index) ||
            string(json_node, context, index));
}

bool ParserJson::elements(JsonVariant::json_pair* json_node, const std::string &context,
                          int index)
{
    int idx = 0;
    return ( value(json_node, context) &&
            repeater([this, json_node, context, idx] () {
                int i = idx;
                if (!context.empty())
                    ++i;
                return(readChar(',') && value(json_node, context, i));
            }, '*'));
}

bool ParserJson::array(JsonVariant::json_pair* json_node, const std::string &context,
                       int index)
{
    bool ret = readChar('[');
    if (ret)
    {
        std::string ctx = _tmp_data;
        if (!context.empty())
        {
            ret = ret &&
                  repeater([this, json_node, ctx, index, context] () {
                      return (elements((*boost::get<JsonVariant::json_array *&>((*json_node)[context].getValue()))[index], ctx, index));
                  }, '?') &&
                  readChar(']');
        }
        else
            ret = ret &&
                    repeater([this, json_node, ctx, index] () {
                        return (elements(json_node, ctx, index));
                    }, '?') &&
                    readChar(']');
    }
    else
        ret = ret &&
                repeater([this, json_node, context, index] () {
                    return (elements(json_node, context, index));
                }, '?') &&
                readChar(']');
    return (ret);
}

bool ParserJson::parse(JsonVariant::json_pair* content)
{
    _comment= '#';
    _ignore= "\t\n ";
    bool ret;
    try
    {
        ret = object(content) && readUntilEOF();
    }
    catch (std::exception const &e)
    {
        std::cerr << "Json : " << e.what() << std::endl;
        ret = false;
    }
    return (ret);
}