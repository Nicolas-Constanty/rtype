//
// Created by babiole on 17/10/16.
//

#ifndef PAMELA_JSONVARIANT_H
#define PAMELA_JSONVARIANT_H

#include <boost/variant.hpp>
#include <map>
#include <vector>
#include "JsonException.hpp"

class JsonVariant {
public:
    typedef std::map<std::string, JsonVariant>  json_pair;
    typedef std::vector<json_pair *>  json_array;
    typedef boost::variant<std::string, json_array *, json_pair*> bvariant;
public:
    JsonVariant();
    bvariant &getValue();
    const bvariant &get() const;
    json_array *get_array() const;
    const std::string &operator()() const;
	JsonVariant operator[](int key) const;
	const JsonVariant &operator[](const std::string &name) const;
    size_t size() const;
	
private:
    bvariant value;
};


//
//class json_visitor_a : public boost::static_visitor<JsonVariant::json_array *>
//{
//public:
//	JsonVariant::json_array *operator()(JsonVariant::json_array *elem) const
//	{
//		return elem;
//	}
//};
//
//class json_visitor_s : public boost::static_visitor<std::string>
//{
//public:
//
//	const std::string & operator()(const std::string & str) const
//	{
//		return str;
//	}
//};

class json_visitor_p : public boost::static_visitor<JsonVariant::json_pair *>
{
public:

	JsonVariant::json_pair *operator()(JsonVariant::json_pair *elem) const
	{
		return elem;
	}
};


class JSON_VALUE;
typedef std::map<std::string, JSON_VALUE *> json_pair;

class JSON_VALUE
{
public:
	JSON_VALUE() : m_float(0), m_int(0), m_val("") {};
private:
	float						m_float;
	int							m_int;
	std::string					m_val;
	std::vector<JSON_VALUE *>	m_array;
	json_pair					m_object;

public:
	JSON_VALUE *operator[](const std::string &name)
	{
		return m_object[name];
	}

	const std::vector<JSON_VALUE *> &GetArray() const
	{
		return m_array;
	}

	const std::string &GetString() const
	{
		return m_val;
	}

	int  GetInt()
	{
		return m_int;
	}
};


#endif //PAMELA_JSONVARIANT_H
