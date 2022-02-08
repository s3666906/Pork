/****************************************************************************
 * Object Oriented Programming Using C++ CPT323
 * Assignment 2 - RMIT SP1 2020
 * @author Miroslav Petkovic s3666906 & Jarryd Semmens
 * DIRECTION
 * Lookup tables for easy conversion of strings to enums
 *
 ****************************************************************************/

#pragma once

#include <string>
#include <boost/algorithm/string/case_conv.hpp>
#include <map>

enum Direction
{
	NORTH,
	EAST,
	SOUTH,
	WEST
};

enum UserCommands
{
	PICKUP,
	WEAR,
	REMOVE,
	DROP,
	SAVE,
	LOOK,
	EXITS,
	AREAS,
	AREA,
	MOVE,
	OPEN,
	CLOSE,
	QUIT
};

enum WearPosition : int
{
	Head,
	Arms,
	Hands,
	Torso,
	Wrists,
	Legs,
	Feet,
	Weapon,
	Shield,
	Held
};

enum SaveType
{
	BINARY,
	ASCII
};

class EnumParser
{
	EnumParser();

	std::map<std::string, UserCommands> UserCommandsVsStringTable;
	std::map<UserCommands, std::string> StringVsUserCommandsTable;

	std::map<std::string, Direction> DirectionVsStringTable;
	std::map<Direction, std::string> StringVsDirectionTable;

	std::map<std::string, WearPosition> WearPositionVsStringTable;
	std::map<WearPosition, std::string> StringVsWearPositionTable;

	std::map<std::string, SaveType> SaveTypeVsStringTable;
	std::map<SaveType, std::string> StringVsSaveTypeTable;

public:
	static EnumParser& GetInstance();

	bool TryParse(std::string in_String, UserCommands& in_Command);
	bool TryParse(std::string in_String, Direction& in_Direction);
	bool TryParse(std::string in_String, WearPosition& in_Position);
	bool TryParse(std::string in_String, SaveType& in_SaveType);

	std::string EnumToString(UserCommands in_Enum);
	std::string EnumToString(Direction in_Enum);
	std::string EnumToString(WearPosition in_Enum);
	std::string EnumToString(SaveType in_Enum);
};


