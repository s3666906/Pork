/****************************************************************************
 * Object Oriented Programming Using C++ CPT323
 * Assignment 2 - RMIT SP1 2020
 * @author Miroslav Petkovic s3666906
 * AREA
 * An essential gameplay element, loaded from disk and interacted with
 * by players
 ****************************************************************************/

#include "Area.h"

Area::Area()
{
}

bool Area::Load(std::vector<std::string> in_Line)
{
	//Global ID for area
	Id = std::stoi(in_Line[0]);

	//Area name
	Name = in_Line[1];

	//Description of area
	Description = in_Line[2];

	return true;
}
