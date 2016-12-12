//
// Created by babiole on 17/10/16.
//

#include <boost/exception/exception.hpp>
#include "Parser/JsonVariant.hpp"

JsonVariant::JsonVariant()
{

};

JsonVariant::bvariant &JsonVariant::getValue()
{
    return value;
};
const JsonVariant::bvariant &JsonVariant::get() const
{
    return value;
};


JsonVariant::json_array *JsonVariant::get_array() const
{
    return boost::get<json_array *>(value);
};

const std::string &JsonVariant::operator()() const
{
    
	try
	{
		const std::string &s = boost::get<std::string>(value);
		return (s);
	}
	catch(const std::exception &e)
	{
		(void)e;
		json_pair *p = boost::get<json_pair *>(value);
		const std::string &s = boost::get<std::string>(p->begin()->second.getValue());
		return (s);
	}
}

JsonVariant JsonVariant::operator[](int key) const
{
    try {
        json_array *a = boost::get<json_array *>(value);
        if (key >= static_cast<int>(a->size()))
            throw JsonException("Out of Range");
		JsonVariant p;
		p.getValue() = (*a)[key];
		return p;
    }
    catch (boost::exception const &e) {
		(void)e;
        throw JsonException("Element is not an array");
    }
}

const JsonVariant &JsonVariant::operator[](const std::string & name) const
{
	
	std::map<std::string, JsonVariant> *p = boost::get<std::map<std::string, JsonVariant> *>(value);
	//const std::string &s = boost::get<std::string>((*p)[name].get());
	return (*p)[name];
}

size_t JsonVariant::size() const
{
    return boost::get<json_array *>(value)->size();
}

//std::map<std::string, JsonVariant> operator()()
//{
//
//}
