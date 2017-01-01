#if _WIN32
#include "Common/Flags.hpp"
#include "Common/getopt.h"
#else
#include "Common/Flags.hpp"
#endif

void Flags::Bool(bool & var, char shortFlag, std::string longFlag, std::string description, std::string descriptionGroup) {
	struct option op;
	this->entry(op, shortFlag, longFlag, "(unset)", description, descriptionGroup);

	op.has_arg = no_argument;
	var = false;

	this->setters[op.val] = [&var](std::string) {
		var = true;
	};

	this->options.push_back(op);
}

bool Flags::Parse(int argc, char ** argv) {
	this->options.push_back({ NULL, 0, NULL, 0 });
	int ch;
	while ((ch = getopt_long(argc, argv, this->optionStr.c_str(), &this->options[0], NULL)) != -1) {
		auto it = this->setters.find(ch);
		if (it != this->setters.end()) {
			if (optarg) {
				it->second(optarg);
			}
			else {
				it->second("");
			}
		}
		else {
			return false;
		}
	}
	return true;
}

void Flags::PrintHelp(char * argv0, std::ostream & to) {
	to << "Usage: " << argv0 << " [options]" << std::endl << std::endl;
	for (auto& it : this->help) {
		if (it.first.size()) {
			to << it.first << ":" << std::endl;
		}
		for (auto& h : it.second) {
			to << h << std::endl;
		}
		to << std::endl;
	}
}

void Flags::Reset(void)
{
	optind = 1;
}

template <>
void Flags::set<std::string>(std::string & var, std::string optarg) {
	var = optarg;
}