/******************************************************************************
 *
 * Jarryd Semmens					EXITMANAGER						COSC2140
 *
 * Loads all the exits for all the rooms
 *
 *****************************************************************************/

#pragma once

#include "Item.h"
#include "Door.h"
#include "ManagerBase.h"

class DoorManager : public ManagerBase
{
	bool ProcessLine(std::vector<std::string> in_Line) override;

public:
	std::map<int, std::unique_ptr<Door>> DoorCollection;

	explicit DoorManager();
	void LoadContent(std::string in_PlayerName);
	void GetDoorsForRoom(int in_RoomID, int in_Doors[4], int& in_ExitCount);
	bool Save();
};
