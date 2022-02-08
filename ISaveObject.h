/******************************************************************************
 *
 * Jarryd Semmens					ISaveObject						COSC2140
 *
 * Interface to allow easy save to string
 *
 *****************************************************************************/
#pragma once

#include <string>

class ISaveObject
{
	virtual std::string Save() = 0;
};
