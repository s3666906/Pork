/******************************************************************************
 *
 * Jarryd Semmens					PORKGAME						COSC2140
 *
 * The "Game" object, containing the gameplay loop and components to make
 * everything happen within!
 * Also handles command parsing
 *
 *****************************************************************************/

#pragma once

#include <string>
#include <iostream>
#include "AreaManager.h"
#include "DoorManager.h"
#include "ItemManager.h"
#include "PlayerManager.h"
#include "RoomManager.h"
#include "RoomStateManager.h"
#include "StringHelper.h"
#include <boost/filesystem/operations.hpp>
#include <boost/filesystem/path.hpp>

class PorkGame
{
	bool GameOn = true;
	const int ApplicationVersionMajor = 1;
	const int ApplicaitonVersionMinor = 2;
	std::hash<std::basic_string<char>> StringHasher;

	bool Login();
	
	void Input();
	void Update();
	void Render();
	void AddRandomItems();

	bool Pickup(std::string in_Input);
	bool Drop(std::string in_Input);
	bool Wear(std::string in_Input);
	bool Remove(std::string in_Input);
	void Look();
	void DisplayAllAreas();
	void DisplayCurrentArea();
	void DisplayExits();
	bool Move(std::string in_Input);
	bool SetDoorState(std::string in_Input, bool in_IsOpen);
	bool Save(std::string in_Input);
	void Quit();

public:
	PorkGame();
	static PorkGame& GetInstance();

	std::unique_ptr<PlayerManager> Players;
	std::unique_ptr<ItemManager> Items;
	std::unique_ptr<RoomManager> Rooms;
	std::unique_ptr<DoorManager> Doors;
	std::unique_ptr<AreaManager> Areas;
	std::unique_ptr<RoomStateManager> RoomStates;

	void Run();
	void LoadContent();
	void Initialize();

	bool Parse(std::string in_Line);
};
