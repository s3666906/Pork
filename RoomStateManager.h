/******************************************************************************
 *
 * Jarryd Semmens				ROOMSTATEMANAGER					COSC2140
 *
 * Loads up, and manages doors and item contents in rooms
 *
 *****************************************************************************/

#pragma once

#include "ManagerBase.h"
#include "RoomState.h"
#include "ItemManager.h"

class RoomStateManager : public ManagerBase
{
	bool ProcessLine(std::vector<std::string> in_Line) override;

public:
	explicit RoomStateManager();
	std::map<int, std::unique_ptr<RoomState>> RoomStateCollection;
	void LoadContent(std::string in_PlayerName);
	bool Save();
};
