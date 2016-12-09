#include <string>
#include "Parser/ParserJson.hpp"
#include "Parser/Parser.hpp"

int main(int ac, char **av)
{
	if (ac < 2)
	{
		std::cout << "Please give arguments" << std::endl;
		return 1;
	}
	Parser parser = Parser(JSON, av[1]);
	JsonVariant::json_pair map;
	if (parser.parse(&map))
	{
		std::cout << &map << std::endl;
		std::cout << "SPEED " << map["stages"][0]["speed"]() << std::endl;
		//std::cout << map["rect"]["y"]() << std::endl;
	}
	else
	{
		std::cout << "Fail" << std::endl;
		std::cout << &map << std::endl;
	}
	while (true)
	{

	}
	return (0);
}