/******************************************************************************
 *
 * Jarryd Semmens					ITEMMANAGER						COSC2140
 *
 * Loads items, and manages their usage
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
#include <boost/random.hpp>
#include <ctime>
#include <cstdint>
#include "Item.h"
#include "EnumParser.h"
#include "ManagerBase.h"
#include "RoomManager.h"

class ItemManager : public ManagerBase
{
protected:
	bool ProcessLine(std::vector<std::string> in_Line) override;

public:
	explicit ItemManager();
	std::map<int, std::unique_ptr<Item>> ItemCollection;
	int ItemCount = 0;
};
