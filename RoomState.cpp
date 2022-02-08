/******************************************************************************
 *
 * Jarryd Semmens					ROOMSTATE						COSC2140
 *
 * Mutable, saveable states for each room, that are saved to disk
 *
 *****************************************************************************/

#include "RoomState.h"

#include "DoorManager.h"

RoomState::RoomState(int in_Id)
{
	RoomId = in_Id;
}

std::string RoomState::Save()
{
	std::string retVal;

	//and finally, each item in sequence
	for (size_t i = 0; i < Pickups.size(); i++)
	{
		//Room ID
		retVal += std::to_string(this->RoomId) + "\t";

		//Item Id
		retVal += std::to_string(Pickups[i]) + "\n";
	}

	return retVal;
}
