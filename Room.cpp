/******************************************************************************
 *
 * Jarryd Semmens					ROOM						COSC2140
 *
 *  An essential gameplay element, loaded from disk and interacted with
 *  by players
 *
 *****************************************************************************/

#include "Room.h"

Room::Room()
{
}

bool Room::Load(std::vector<std::string> in_Line)
{
	//Global ID
	Id = std::stoi(in_Line[0]);

	//Area Room Number
	AreaRoomNumber = std::stoi(in_Line[1]);

	//Area Number
	AreaId = std::stoi(in_Line[2]);

	//Name
	Name = in_Line[3];

	//Description
	Description = in_Line[4];

	return true;
}
