/******************************************************************************
 *
 * Jarryd Semmens					ROOMSTATE						COSC2140
 *
 * Mutable, saveable states for each room, that are saved to disk
 *
 *****************************************************************************/

#pragma once

#include <vector>

#include "Door.h"

class RoomState : public ISaveObject
{
public:
	int RoomId;
	std::vector<int> Pickups; //We only store id's. Items are owned by the manager

	RoomState(int in_Id);

	std::string Save() override;
};
