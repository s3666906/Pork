/******************************************************************************
 *
 * Jarryd Semmens					ILoadObject						COSC2140
 *
 * Interface to parse a broken up string into an object
 *
 *****************************************************************************/

#pragma once

#include <string>
#include <vector>

class ILoadObject
{
	virtual bool Load(std::vector<std::string> in_Line) = 0;
};
