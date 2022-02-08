#include "Item.h"

Item::Item()
{
	EquipPosition = WearPosition::Held;
	Id = -1;
	Value = -1;
}

bool Item::Load(std::vector<std::string> in_Line)
{
	//Id number
	Id = std::stoi(in_Line[0]);

	//Location
	if (!EnumParser::GetInstance().TryParse(in_Line[1], EquipPosition))
	{
		//Failed to parse item			
		return false;
	}

	//Name
	Name = in_Line[2];

	//Description
	Description = in_Line[3];

	//Value
	Value = std::stoi(in_Line[4]);

	return true;
}
