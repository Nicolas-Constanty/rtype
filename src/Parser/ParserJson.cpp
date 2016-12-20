//
// Created by consta_n on 9/19/16.
//

#include "Parser/ParserJson.hpp"

ParserJson::ParserJson(ProducterStream &ps) : ConsumerParser(ps), m_type(NONE), m_root(nullptr)
{
	key = false;
	m_key = false;
}

bool ParserJson::object()
{
	bool ret = readChar('{');
	if (!_tmp_data.empty() && ret && m_array.empty())
	{
		(*m_parent.top())[_tmp_data].getValue() = new JsonVariant::json_pair();
		m_parent.push(boost::get<JsonVariant::json_pair *>((*m_parent.top())[_tmp_data].get()));
	}
	ret = ret &&
		repeater([this] {
		return (members());
	}, '?') &&
		readChar('}');
	if (!m_parent.empty() && m_parent.top() != m_root)
		m_parent.pop();
    return (ret);
}

bool ParserJson::members()
{
    return (pair() &&
            repeater([this] () {
                return (readChar(',') && pair());
            }, '*'));
}

bool ParserJson::save_key()
{
    beginCapture("key");
    bool ret = ConsumerParser::readValue();
    endCapture("key", _tmp_data);
	m_key = true;
    return (ret);
}

bool ParserJson::save_value()
{
    std::string val;
    beginCapture("value");
    bool ret = readValue();
    endCapture("value", val);
	JsonVariant::json_array *a;
	if (!m_array.empty())
	{
		try
		{
			a = boost::get<JsonVariant::json_array *>((*m_parent.top())[m_array].getValue());
			if (m_array != _tmp_data)
			{
				(*a).push_back(new JsonVariant::json_pair());
				(*(*a).back())[_tmp_data].getValue() = val;
			}
			else
			{
				(*a).push_back(new JsonVariant::json_pair());
				(*(*a).back())[std::to_string((*a).size() - 1)].getValue() = val;
			}
		}
		catch (const std::exception&)
		{
			std::cout << "Cannot add map " << _tmp_data << " " << val << std::endl;
		}
	}
	else if (!_tmp_data.empty())
	{
		(*m_parent.top())[_tmp_data].getValue() = val;
	}
	m_key = false;
    return (ret);
}

bool ParserJson::string()
{
    bool ret = readChar('"');
    if (key)
        ret = ret && save_key();
    else
        ret = ret && save_value();
    return (ret && readChar('"'));
}

bool ParserJson::pair()
{
    bool ret;
    key = true;
    ret = value();
    key = false;
    return (ret && readChar(':') && value());
}

bool ParserJson::value()
{
    return (string() ||
			array()||
			object());
}

bool ParserJson::elements()
{
    return ( value() &&
            repeater([this] () {
                return(readChar(',') && value());
            }, '*'));
}

bool ParserJson::array()
{
    bool ret = readChar('[');
    if (ret)
    {
		m_array = _tmp_data;
		(*m_parent.top())[_tmp_data].getValue() = new JsonVariant::json_array();
		ret = ret &&
			repeater([this]() {
			return (elements());
		}, '?') &&
			readChar(']');
		m_array.clear();
    }
    else
        ret = ret &&
                repeater([this] () {
                    return (elements());
                }, '?') &&
                readChar(']');
    return (ret);
}

bool ParserJson::parse(JsonVariant::json_pair* content)
{
    _comment= '#';
    _ignore= "\t\n\r ";
    bool ret;
    try
    {
		m_root = content;
		m_parent.push(m_root);
        ret = object() && readUntilEOF();
    }
    catch (std::exception const &e)
    {
        std::cerr << "Json : " << e.what() << std::endl;
        ret = false;
    }
    return (ret);
}