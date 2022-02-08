/****************************************************************************
 * Object Oriented Programming Using C++ CPT323
 * Assignment 2 - RMIT SP1 2020
 * @author Miroslav Petkovic s3666906 & Jarryd Semmens
 * DIRECTION
 * Lookup tables for easy conversion of strings to enums
 *
 ****************************************************************************/
#include "EnumParser.h"

EnumParser::EnumParser()
{
	UserCommandsVsStringTable["PICKUP"] = PICKUP;
	UserCommandsVsStringTable["WEAR"] = WEAR;
	UserCommandsVsStringTable["REMOVE"] = REMOVE;
	UserCommandsVsStringTable["DROP"] = DROP;
	UserCommandsVsStringTable["SAVE"] = SAVE;
	UserCommandsVsStringTable["LOOK"] = LOOK;
	UserCommandsVsStringTable["EXITS"] = EXITS;
	UserCommandsVsStringTable["AREAS"] = AREAS;
	UserCommandsVsStringTable["AREA"] = AREA;
	UserCommandsVsStringTable["MOVE"] = MOVE;
	UserCommandsVsStringTable["OPEN"] = OPEN;
	UserCommandsVsStringTable["CLOSE"] = CLOSE;
	UserCommandsVsStringTable["QUIT"] = QUIT;

	auto itrCommand = UserCommandsVsStringTable.begin();
	while (itrCommand != UserCommandsVsStringTable.end())
	{
		StringVsUserCommandsTable[itrCommand->second] = itrCommand->first;
		++itrCommand;
	}

	DirectionVsStringTable["NORTH"] = NORTH;
	DirectionVsStringTable["EAST"] = EAST;
	DirectionVsStringTable["SOUTH"] = SOUTH;
	DirectionVsStringTable["WEST"] = WEST;

	auto itrDirection = DirectionVsStringTable.begin();
	while (itrDirection != DirectionVsStringTable.end())
	{
		StringVsDirectionTable[itrDirection->second] = itrDirection->first;
		++itrDirection;
	}

	WearPositionVsStringTable["HEAD"] = Head;
	WearPositionVsStringTable["ARMS"] = Arms;
	WearPositionVsStringTable["HANDS"] = Hands;
	WearPositionVsStringTable["TORSO"] = Torso;
	WearPositionVsStringTable["WRISTS"] = Wrists;
	WearPositionVsStringTable["LEGS"] = Legs;
	WearPositionVsStringTable["FEET"] = Feet;
	WearPositionVsStringTable["WEAPON"] = Weapon;
	WearPositionVsStringTable["SHIELD"] = Shield;
	WearPositionVsStringTable["HELD"] = Held;

	auto itrWearPosition = WearPositionVsStringTable.begin();
	while (itrWearPosition != WearPositionVsStringTable.end())
	{
		StringVsWearPositionTable[itrWearPosition->second] = itrWearPosition->first;
		++itrWearPosition;
	}

	SaveTypeVsStringTable["BINARY"] = SaveType::BINARY;
	SaveTypeVsStringTable["ASCII"] = SaveType::ASCII;

	auto itrWearSave = SaveTypeVsStringTable.begin();
	while (itrWearSave != SaveTypeVsStringTable.end())
	{
		StringVsSaveTypeTable[itrWearSave->second] = itrWearSave->first;
		++itrWearSave;
	}
}

EnumParser& EnumParser::GetInstance()
{
	static EnumParser instance;
	return instance;
}

bool EnumParser::TryParse(std::string in_String, UserCommands& in_Command)
{
	boost::to_upper(in_String);

	auto itr = UserCommandsVsStringTable.find(in_String);

	if (itr == UserCommandsVsStringTable.end())
		return false;

	in_Command = itr->second;
	return true;
}

bool EnumParser::TryParse(std::string in_String, Direction& in_Direction)
{
	boost::to_upper(in_String);

	auto itr = DirectionVsStringTable.find(in_String);

	if (itr == DirectionVsStringTable.end())
		return false;

	in_Direction = itr->second;
	return true;
}

bool EnumParser::TryParse(std::string in_String, WearPosition& in_Position)
{
	boost::to_upper(in_String);

	auto itr = WearPositionVsStringTable.find(in_String);

	if (itr == WearPositionVsStringTable.end())
		return false;

	in_Position = itr->second;
	return true;
}

bool EnumParser::TryParse(std::string in_String, SaveType& in_SaveType)
{
	boost::to_upper(in_String);

	auto itr = SaveTypeVsStringTable.find(in_String);

	if (itr == SaveTypeVsStringTable.end())
		return false;

	in_SaveType = itr->second;
	return true;
}

std::string EnumParser::EnumToString(UserCommands in_Enum)
{
	return StringVsUserCommandsTable[in_Enum];
}

std::string EnumParser::EnumToString(Direction in_Enum)
{
	return StringVsDirectionTable[in_Enum];
}

std::string EnumParser::EnumToString(WearPosition in_Enum)
{
	return StringVsWearPositionTable[in_Enum];
}
