/******************************************************************************
 *
 * Jarryd Semmens					STRINGTOOLS						COSC2140
 *
 * Helper functions that are to be re-used across multiple assignments
 * and exercises.
 *
 *****************************************************************************/

#pragma once

#include <string>

class StringHelper
{
	std::string LegalCharacters;

	StringHelper();
	bool IsLegalCharacter(char& in_C);

public:
	static StringHelper& GetInstance();
	void SanitizeString(std::string& in_String);
	std::string ToString(bool in_Bool);
};
