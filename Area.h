/****************************************************************************
 * Object Oriented Programming Using C++ CPT323
 * Assignment 2 - RMIT SP1 2020
 * @author Miroslav Petkovic s3666906
 * AREA
 * An essential gameplay element, loaded from disk and interacted with
 * by players
 ****************************************************************************/

#pragma once

#include <string>
#include "ILoadObject.h"

class Area : ILoadObject
{
public:
	int Id;
	std::string Name;
	std::string Description;

	Area();

	bool Load(std::vector<std::string> in_Line) override;
};
