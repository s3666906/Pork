/******************************************************************************
 *
 * Jarryd Semmens					DOOR						COSC2140
 *
 *  Doors can be opened and closed, link rooms and be saved to disk
 *
 *****************************************************************************/

#pragma once

#include <boost/lexical_cast.hpp>
#include "ILoadObject.h"
#include "ISaveObject.h"
#include "Item.h"
#include "MathHelper.h"

class Door : public ILoadObject, public ISaveObject
{
public:
	int Id;
	int EntranceRoomId;
	int ExitRoomId;
	bool IsOpen;
	Direction Location;

	Door();
	bool SetState(bool in_IsOpen);
	bool Load(std::vector<std::string> in_Line) override;
	std::string Save() override;
};
