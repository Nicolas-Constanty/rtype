#include "Parser/Parser.hpp"

Parser::Parser (int type)
{
    FP funcs[3] = {&Parser::init_Conf, &Parser::init_Http, &Parser::init_Json};
    if (!_ps.loadStdin())
        throw std::runtime_error("Cannot open this file");
    (this->*funcs[type])();
}


Parser::Parser (int type, char *filename)
{
    FP funcs[3] = {&Parser::init_Conf, &Parser::init_Http, &Parser::init_Json};
    if (!_ps.loadFile(filename))
        throw std::runtime_error("Cannot open this file");
    (this->*funcs[type])();
}

Parser::~Parser()
{
    delete _pc;
}

void Parser::init_Conf()
{
    _pc = new ParserConf(_ps);
}

void Parser::init_Http()
{
    _pc = new ParserHttp(_ps);
}

void Parser::init_Json()
{
    _pc = new ParserJson(_ps);
}

bool Parser::parse(JsonVariant::json_pair *content)
{
    return _pc->parse(content);
}

std::ostream& operator<<(std::ostream& out, JsonVariant::bvariant var)
{

    try {
        out << "\"" << boost::get<std::string>(var) << "\"}";
    }
    catch (std::exception const &e) {
        try {
            out << "[" << std::endl;
            JsonVariant::json_array *a = boost::get<JsonVariant::json_array *>(var);
            out << a;
        }
        catch (std::exception const &e) {
            try {
                JsonVariant::json_pair p = boost::get<JsonVariant::json_pair>(var);
                out << &p;
            }
            catch (std::exception const &e) {
                throw JsonException("Invalid map");
            }
        }
    }
    return out;
}
std::ostream& operator<<(std::ostream& out, const JsonVariant::json_array* jsarray)
{
    static unsigned long indent = 0;
    ++indent;
    for (int j = 0; j < jsarray->size(); ++j) {
        JsonVariant::json_pair *elem = (*jsarray)[j];
        int n = 0;
        for (JsonVariant::json_pair::const_iterator k = elem->begin(); k != elem->end(); ++k) {
            if (!n)
                out << std::string(indent * 4, ' ');
            ++n;
            out << "{\"" << (*k).first << "\" : \"" << (*k).second.get();
            if (n != elem->size())
                out << ", ";
        }
        if (j < jsarray->size() - 1)
            out << ", " << std::endl;
        else if (indent != 1)
            out << std::string(--indent * 4, ' ') << "]}";
        else
            out << std::endl << "]}";
    }
    return out;
}

std::ostream& operator<<(std::ostream& out, const JsonVariant::json_pair* json)
{
    int n = 0;
    for (JsonVariant::json_pair::const_iterator i = json->begin(); i != json->end(); i++) {
        out << "{\"" << (*i).first << "\" : " << ((*i).second).get();
        ++n;
        if (n != json->size())
            out << ", ";
    }
    return out;
}