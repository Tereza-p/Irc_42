//
// Created by jazema on 01/04/2026.
//

#include "StringHelper.hpp"
#include <set>
#include <vector>

bool StringHelper::startsWith(const std::string &reference, const std::string &beginning)
{
	if (beginning.size() > reference.size())
		return (false);
	return (reference.compare(0, beginning.size(), beginning) == 0);
}

void	StringHelper::printCentered(std::string str, int width, char c)
{
	int padding = (width - str.size()) / 2;
	std::cerr << std::string(padding, c) << str << std::string(padding, c) << std::endl;
}

void StringHelper::replaceChars(std::string &reference, const std::string &matchChars, char replacement)
{
	for (size_t i = 0; i < matchChars.size(); i++)
	{
		for (size_t j = 0; j != std::string::npos; j = reference.find(i))
		{
			reference[j] = replacement;
		}
	}
}

std::string StringHelper::join(const std::vector<std::string> &strings, const std::string &delimiter)
{
	std::string result;

	for (size_t i = 0; i < strings.size(); ++i)
	{
		result += strings[i];
		if (i != strings.size() - 1)
			result += delimiter;
	}
	return (result);
}

std::vector<std::string> StringHelper::split(const std::string &string, const std::string &delimiter)
{
	std::vector<std::string> result;
	size_t start = 0;
	size_t end;

	while ((end = string.find(delimiter, start)) != std::string::npos)
	{
		result.push_back(string.substr(start, end - start));
		start = end + delimiter.length();
	}
	result.push_back(string.substr(start));
	return result;
}
