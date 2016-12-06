//
// Created by babiole on 17/10/16.
//

#include "Parser/JsonVariant.hpp"

JsonVariant::JsonVariant()
{
    value = nullptr;
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
    const std::string &s = boost::get<std::string>(value);
    return (s);
}

std::map<std::string, JsonVariant> &JsonVariant::operator[](int key) const
{
    try {
        json_array *a = boost::get<json_array *>(value);
        if (key >= a->size())
            throw JsonException("Out of Range");
        std::map<std::string, JsonVariant> *p = (*a)[key];
        return (*p);
    }
    catch (boost::exception const &e) {
        throw JsonException("Element is not an array");
    }
}

size_t JsonVariant::size() const
{
    return boost::get<json_array *>(value)->size();
}
