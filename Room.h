/******************************************************************************
 *
 * Jarryd Semmens					ROOM						COSC2140
 *
 *  An essential gameplay element, loaded from disk and interacted with
 *  by players
 *
 *****************************************************************************/

#pragma once

#include <string>
#include "ILoadObject.h"

class Room : ILoadObject
{
public:
	int Id;
	int AreaId;
	int AreaRoomNumber;
	std::string Name;
	std::string Description;

	Room();

	bool Load(std::vector<std::string> in_Line) override;
};
