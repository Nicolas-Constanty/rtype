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
    typedef boost::variant<std::string, json_array *, json_pair> bvariant;
public:
    JsonVariant();
    bvariant &getValue();
    const bvariant &get() const;
    json_array *get_array() const;
    const std::string &operator()() const;
    json_pair &operator[](int key) const;
    size_t size() const;
private:
    bvariant value;
};


#endif //PAMELA_JSONVARIANT_H
