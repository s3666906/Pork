/******************************************************************************
 *
 * Jarryd Semmens				ROOMSTATEMANAGER					COSC2140
 *
 * Loads up, and manages doors and item contents in rooms
 *
 *****************************************************************************/

#include "RoomStateManager.h"

#include "PorkGame.h"

RoomStateManager::RoomStateManager()
{
	ContentPath = "Content/pickups.txt";
}

void RoomStateManager::LoadContent(std::string in_PlayerName)
{
	UserSavePath = "save/" + in_PlayerName + "/roomstates.txt";
}

bool RoomStateManager::ProcessLine(std::vector<std::string> in_Line)
{
	//Room ID
	int roomID = std::stoi(in_Line[0]);

	//Item ID
	int itemID = std::stoi(in_Line[1]);

	if (RoomStateCollection.find(roomID) == RoomStateCollection.end())
		RoomStateCollection[roomID] = std::make_unique<RoomState>(roomID);

	RoomStateCollection[roomID]->Pickups.push_back(itemID);

	return true;
}

bool RoomStateManager::Save()
{
	boost::filesystem::ofstream destinationFile;
	destinationFile.open(UserSavePath);
		
	if (!destinationFile.is_open())
	{
		std::cerr << "Failed to open '" << UserSavePath << "'\n";
		return false;
	}

	for (auto itr = RoomStateCollection.begin(); itr != RoomStateCollection.end(); ++itr)
	{
		destinationFile << itr->second->Save();
	}

	return true;
}
