#include "Door.h"
#include "StringHelper.h"

Door::Door()
{
	EntranceRoomId = 0;
	ExitRoomId = 0;
	Id = -1;
	IsOpen = true;
	Location = Direction::NORTH;
}

bool Door::SetState(bool in_IsOpen)
{
	if (in_IsOpen == IsOpen)
		return false;

	IsOpen = in_IsOpen;
	return true;
}

bool Door::Load(std::vector<std::string> in_Line)
{
	EntranceRoomId = std::stoi(in_Line[0]);
	ExitRoomId = std::stoi(in_Line[1]);

	if (!EnumParser::GetInstance().TryParse(in_Line[2], Location))
	{
		//Failed to parse item			
		return false;
	}

	IsOpen = in_Line[3] == "true";

	Id = MathHelper::CantorPair(EntranceRoomId, ExitRoomId);
	return true;
}

std::string Door::Save()
{
	std::string line = std::to_string(EntranceRoomId) + "\t" + std::to_string(ExitRoomId);
	line += "\t" + EnumParser::GetInstance().EnumToString(Location);
	line += "\t" + StringHelper::GetInstance().ToString(IsOpen);

	return line;
}
