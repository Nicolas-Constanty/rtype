#include "Common/Debug.hpp"

// DEFAULT, ERROR, SUCCESS, WARNING

#if _WIN32
const WORD Debug::colors[] = { 0x07, 0x04, 0x02, 0x06, 0x09 };
#else
const char* const Debug::colors[] = { "\e[39m", "\e[31m", "\e[32m", "\e[33m", "\e[34m" };
#endif
	
void Debug::PrintError(const std::string & msg)
{
	PrintColor("Error : " + msg, RED);
}

void Debug::PrintWarning(const std::string & msg)
{
	PrintColor("Warning : " + msg, YELLOW);
}

void Debug::PrintSuccess(const std::string & msg)
{
	PrintColor("Success : " + msg, GREEN);
}

void Debug::PrintInfo(const std::string & msg)
{
	PrintColor("Info : " + msg, BLUE);
}

void Debug::Print(const std::string & msg)
{
	std::cout << msg << std::endl;
}

void Debug::PrintColor(const std::string & msg, int index)
{
#if _WIN32
	HANDLE hstdin = GetStdHandle(STD_INPUT_HANDLE);
	HANDLE hstdout = GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(hstdout, &csbi);
	SetConsoleTextAttribute(hstdout, colors[index]);
	if (index == 1)
		std::cerr << msg << std::endl;
	else
		std::cout << msg << std::endl;
	FlushConsoleInputBuffer(hstdin);
	SetConsoleTextAttribute(hstdout, csbi.wAttributes);
#else
	if (index == 1)
		std::cerr << colors[index] << msg << colors[DEFAULT] << std::endl;
	else
		std::cout << colors[index] << msg << colors[DEFAULT] << std::endl;
#endif
}