/******************************************************************************
 *
 * Jarryd Semmens					ITEM						COSC2140
 *
 *  An essential gameplay element, loaded from disk and interacted with
 *  by players
 *
 *****************************************************************************/

#pragma once

#include <string>
#include "ILoadObject.h"
#include "EnumParser.h"

class Item : ILoadObject
{
public:
	int Id;
	WearPosition EquipPosition;
	std::string Name;
	std::string Description;
	int Value;

	Item();

	bool Load(std::vector<std::string> in_Line) override;
};
