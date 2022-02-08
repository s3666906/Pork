/******************************************************************************
 *
 * Jarryd Semmens					STRINGTOOLS						COSC2140
 *
 * Helper functions that are to be re-used across multiple assignments
 * and exercises.
 *
 *****************************************************************************/
#include "StringHelper.h"

#include <ios>
#include <string>

StringHelper::StringHelper()
{
	LegalCharacters = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz ";
}

StringHelper& StringHelper::GetInstance()
{
	static StringHelper instance;
	return instance;
}

void StringHelper::SanitizeString(std::string& in_String)
{
	for (std::string::iterator itr = in_String.begin(); itr != in_String.end();)
	{
		//Remove tabs, newlines, and other junk whitespace
		if (std::isspace((*itr)))
			(*itr) = ' ';

		if (IsLegalCharacter(*itr))
			++itr;
		else
			in_String.erase(itr);
	}
}

std::string StringHelper::ToString(bool in_Bool)
{
	if (in_Bool)
		return "true";
	return "false";
}

bool StringHelper::IsLegalCharacter(char& in_C)
{
	bool found = LegalCharacters.find(in_C) != std::string::npos;
	return found;
}
