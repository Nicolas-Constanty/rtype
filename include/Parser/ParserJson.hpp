//
// Created by consta_n on 9/19/16.
//

#ifndef PARSERJSON_H
#define PARSERJSON_H

#include <stack>
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
	bool m_key;
	enum Type
	{
		NONE,
		OBJECT,
		ARRAY
	};
	Type m_type;
	JsonVariant::json_pair *m_root;
	std::stack<JsonVariant::json_pair *> m_parent;
	std::string m_array;

private:
    bool save_key();
    bool save_value();
    bool members();
    bool pair();
    bool value();
    bool array();
    bool elements();
    bool object();
    bool string();
};

#endif //PARSERJSON_H