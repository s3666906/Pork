#include "DoorManager.h"

DoorManager::DoorManager()
{
	ContentPath = "Content/exits.txt";
}

void DoorManager::LoadContent(std::string in_PlayerName)
{
	UserSavePath = "save/" + in_PlayerName + "/exits.txt";
}

void DoorManager::GetDoorsForRoom(int in_RoomID, int in_Doors[4], int& in_ExitCount)
{
	in_ExitCount = 0;
	auto itr = DoorCollection.begin();

	while (itr != DoorCollection.end())
	{
		if (itr->second->EntranceRoomId == in_RoomID)
		{
			in_Doors[in_ExitCount] = itr->second->Id;
			++in_ExitCount;
		}
		++itr;
	}
}

bool DoorManager::ProcessLine(std::vector<std::string> in_Line)
{
	std::unique_ptr<Door> tmpDoor = std::make_unique<Door>();

	if (!tmpDoor->Load(in_Line))
		return false;

	DoorCollection[tmpDoor->Id] = std::move(tmpDoor);
	return true;
}

bool DoorManager::Save()
{
	boost::filesystem::ofstream destinationFile;
	destinationFile.open(UserSavePath);

	if (!destinationFile.is_open())
	{
		std::cerr << "Failed to open output file\n";
		return false;
	}

	for (auto itr = DoorCollection.begin(); itr != DoorCollection.end(); ++itr)
	{
		destinationFile << itr->second->Save();
		destinationFile << std::endl;
	}

	return true;
}
