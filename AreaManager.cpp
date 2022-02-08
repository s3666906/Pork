/****************************************************************************
 * Object Oriented Programming Using C++ CPT323
 * Assignment 2 - RMIT SP1 2020
 * @author Miroslav Petkovic s3666906
 * AREAMANAGER
 * An essential gameplay element, loads areas and manages their usage
 ****************************************************************************/

#include "AreaManager.h"

AreaManager::AreaManager()
{
	ContentPath = "Content/areas.txt";
}


bool AreaManager::ProcessLine(std::vector<std::string> in_Line)
{
	Area newArea;
	if (!newArea.Load(in_Line))
		return false;

	AreaCollection[newArea.Id] = newArea;
	return true;
}

bool AreaManager::SetCurrentArea(int in_AreaID)
{
	if (AreaCollection.find(in_AreaID) == AreaCollection.end())
		return false;

	CurrentAreaId = in_AreaID;
	return true;
}
