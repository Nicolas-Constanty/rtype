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
	//std::cout << " ============ OBJECT =========== " << std::endl;
	if (!_tmp_data.empty() && ret && m_array.empty())
	{
		//std::cout << "PARENT = " << _tmp_data << std::endl;
		(*m_parent.top())[_tmp_data].getValue() = new JsonVariant::json_pair();
		m_parent.push(boost::get<JsonVariant::json_pair *>((*m_parent.top())[_tmp_data].get()));
		//std::cout << "CHILD = " << m_parent.top() << std::endl;
	}
	ret = ret &&
		repeater([this] {
		return (members());
	}, '?') &&
		readChar('}');
	if (!m_parent.empty() && m_parent.top() != m_root)
		m_parent.pop();
	//_tmp_data.clear();
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
	//std::cout << " ============ KEY =========== " << std::endl;
    beginCapture("key");
    bool ret = ConsumerParser::readValue();
    endCapture("key", _tmp_data);
  //  if (!m_array.empty())
  //  {
		//std::cout << "FDP" << std::endl;
  //      JsonVariant::json_array a = boost::get<JsonVariant::json_array>(
  //              (*json_node)[m_array].get());
		//std::cout << "FDP" << std::endl;
  //      if (!a)
  //          a = new std::vector<JsonVariant::json_pair *>();
  //      /*if (a->size() >= index)
  //      {
  //          JsonVariant::json_pair *p = new JsonVariant::json_pair();
  //          a->push_back(p);
  //      }*/
  //  }
	/*if (!_tmp_data.empty() && m_key == true)
	{
		(*m_parent.front())[last].getValue() = new JsonVariant::json_pair();
		m_current = boost::get<JsonVariant::json_pair *>((*m_parent.front())[last].get());
	}*/
	m_key = true;
    return (ret);
}

bool ParserJson::save_value()
{
	//std::cout << " ============ VALUE =========== " << std::endl;
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
			std::cout << "Cannot add map " << _tmp_data << "     " << val << std::endl;
			//if (!_tmp_data.empty())
			//{
			//	//std::cout << m_parent.top() << std::endl;
			//	(*m_parent.top())[_tmp_data].getValue() = val;
			//}
		}
	}
	else if (!_tmp_data.empty())
	{
		//std::cout << m_parent.top() << std::endl;
		(*m_parent.top())[_tmp_data].getValue() = val;
	}
    /*if (!m_array.empty())
    {
		JsonVariant::json_array *a = nullptr;
		try
		{

			a = boost::get<JsonVariant::json_array *>(
				(*m_parent.front())[m_array].getValue());
		}
		catch (const std::exception&)
		{
			(*m_parent.front())[m_array].getValue() = new JsonVariant::json_array();
			a = boost::get<JsonVariant::json_array *>((*m_parent.front())[m_array].getValue());
		}
        
        if (a)
        {
			if (m_current)
			{
				(*a).push_back(new JsonVariant::json_pair());
				(*(*a).back())[_tmp_data].getValue() = val;
			}
        }
        else
            throw JsonException("Invalid array");
    }
	else 
		*/
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
		std::cout << "ARRAY" << m_array << std::endl;
		(*m_parent.top())[_tmp_data].getValue() = new JsonVariant::json_array();
		ret = ret &&
			repeater([this]() {
			return (elements());
		}, '?') &&
			readChar(']');
		m_array.clear();
		std::cout << std::boolalpha << ret << std::endl;
        /*std::string ctx = _tmp_data;
        if (!context.empty())
        {
            ret = ret &&
                  repeater([this, json_node, ctx, index, context] () {
                      return (elements((*boost::get<JsonVariant::json_array *&>((*json_node)[context].getValue()))[index], ctx, index));
                  }, '?') &&
                  readChar(']');
        }
        else
			std::cout << "ARRAY : " << ctx << std::endl;
            ret = ret &&
                    repeater([this, json_node, ctx, index] () {
                        return (elements(json_node, ctx, index));
                    }, '?') &&
                    readChar(']');*/
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
		std::cout << "ROOT ====> " << m_root << std::endl;
        ret = object() && readUntilEOF();
    }
    catch (std::exception const &e)
    {
        std::cerr << "Json : " << e.what() << std::endl;
        ret = false;
    }
    return (ret);
}