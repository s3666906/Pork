/******************************************************************************
 *
 * Jarryd Semmens					ROOMMANAGER						COSC2140
 *
 * Loads rooms, and manages their usage
 *
 *****************************************************************************/
#include "RoomManager.h"

RoomManager::RoomManager()
{
	ContentPath = "Content/rooms.txt";
}

bool RoomManager::SetCurrentRoom(int in_RoomID)
{
	if (RoomCollection.find(in_RoomID) == RoomCollection.end())
		return false;

	CurrentRoomId = in_RoomID;
	return true;
}

bool RoomManager::ProcessLine(std::vector<std::string> in_Line)
{
	std::unique_ptr<Room> tmpRoom = std::make_unique<Room>();

	if (!tmpRoom->Load(in_Line))
		return false;

	RoomCollection[tmpRoom->Id] = std::move(tmpRoom);
	return true;
}
