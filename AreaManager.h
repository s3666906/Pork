/****************************************************************************
 * Object Oriented Programming Using C++ CPT323
 * Assignment 2 - RMIT SP1 2020
 * @author Miroslav Petkovic s3666906
 * AREAMANAGER
 * An essential gameplay element, loads areas and manages their usage
 ****************************************************************************/

#pragma once

#include <map>
#include <string>
#include <fstream>
#include <iostream>
#include <boost/algorithm/string.hpp>
#include <boost/filesystem/path.hpp>
#include <boost/filesystem/fstream.hpp>
#include "ManagerBase.h"
#include "Area.h"

class AreaManager : public ManagerBase
{
protected:
	bool ProcessLine(std::vector<std::string> in_Line) override;

public:
	std::map<int, Area> AreaCollection;
	int CurrentAreaId;

	AreaManager();
	bool SetCurrentArea(int in_AreaID);
};
