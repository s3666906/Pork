/******************************************************************************
 *
 * Jarryd Semmens					ROOMMANAGER						COSC2140
 *
 * Loads rooms, and manages their usage
 *
 *****************************************************************************/

#pragma once

#include <map>
#include <string>
#include <fstream>
#include <iostream>

#include <boost/algorithm/string.hpp>
#include <boost/filesystem/path.hpp>
#include <boost/filesystem/fstream.hpp>

#include "ManagerBase.h"
#include "Room.h"

class RoomManager : public ManagerBase
{
	bool ProcessLine(std::vector<std::string> in_Line) override;

public:
	RoomManager();
	std::map<int, std::unique_ptr<Room>> RoomCollection;
	int CurrentRoomId;

	bool SetCurrentRoom(int in_RoomID);
};
