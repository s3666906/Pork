/******************************************************************************
 *
 * Jarryd Semmens					MANAGERBASE						COSC2140
 *
 * Helps load up from file, and process the contents into many objects
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

class ManagerBase
{
protected:
	std::string ContentPath;
	std::string UserSavePath;
	virtual bool ProcessLine(std::vector<std::string> in_Line) = 0;
	bool LoadFromFile(std::string in_Path);

public:
	virtual ~ManagerBase() = default;
	bool LoadFromContent();
	virtual bool LoadFromSave();
};
