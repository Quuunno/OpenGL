#include "resources.h"


std::string readText(const char * filename)
{
	std::ifstream file(filename, std::ios::in);
	if (file.is_open())
	{
		std::string result, line;
		while (std::getline(file, line))
		{
			result += line + '\n';
		}
		file.close();
		return result;
	}
	else
		return nullptr;
}
