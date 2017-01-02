//
// Created by consta_n on 9/19/16.
//


#include <iostream>
#include "Parser/ParserHttp.hpp"

ParserHttp::ParserHttp(ProducterStream &ps) : ConsumerParser(ps)
{}

//Http ::= Header '\n' Body;
bool ParserHttp::parse(JsonVariant::json_pair *content)
{
    return (readHeader(content) && readChar('\n') && readBody());
}

//Header ::=  CMD ' ' URI ' ' VERSION '\n' [HeaderList #flush ]*;
bool ParserHttp::readHeader(JsonVariant::json_pair *content)
{
    return (readCMD() && readChar(' ') && readURI() && readChar(' ') && readVersion() && readChar('\n') && repeater([content, this] () { return (readHeaderList(content));}, '*'));
}

//CMD ::= «GET» | «POST» ;
bool ParserHttp::readCMD()
{
    return (readText((char *) "GET") || readText((char *) "POST"));
}

//URI ::= ['/'|'.'|'?'|'%'|'&'|'='|'+'|':'|'-'|'a'..'z'|'A'..'Z'|'0'..'9']+;
bool ParserHttp::readURI()
{
    return (repeater([this] () { return (
            readChar('/')
            || readChar('.')
            || readChar('?')
            || readChar('%')
            || readChar('&')
            || readChar('=')
            || readChar('+')
            || readChar(':')
            || readChar('-')
            || readRange('a', 'z')
            || readRange('A', 'Z')
            || readRange('0', '9'));}, '+'));
}

//VERSION ::= «http/1.0»;
bool ParserHttp::readVersion()
{
    return (readText((char *) "http/1.0"));
}

//HeaderList ::= HeaderName ':' data;
bool ParserHttp::readHeaderList(JsonVariant::json_pair *content)
{
    return (repeater([this, content] () {
        bool ret = readHeaderName() && readChar(':');
        if (ret && !_tmp_data.empty())
            beginCapture(_tmp_data);
        ret = (ret && readData());
        if (!_tmp_data.empty())
            endCapture(_tmp_data,
                       boost::get<std::string>((*content)[_tmp_data].getValue()));
        _tmp_data.clear();
        return ret;
    }, '+'));
}

//HeaderName ::= ['-'|'a'..'z'|'A'..'Z']+;
bool ParserHttp::readHeaderName()
{
    bool ret;
    beginCapture("Name");
    ret = repeater([this] () {
        return (readChar('-') ||
                readRange('a', 'z') ||
                readRange('A', 'Z'));
    }, '+');
    endCapture("Name", _tmp_data);
    return (ret);
}

//data ::= → '\n';
bool  ParserHttp::readData()
{
    return (readUntil('\n'));
}

//Body ::= → EOF //tout jusqu'à EOF;
bool ParserHttp::readBody()
{
    return (readUntilEOF());
}
