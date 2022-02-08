/****************************************************************************
 * Object Oriented Programming Using C++ CPT323
 * Assignment 2 - RMIT SP1 2020
 * @author Miroslav Petkovic s3666906
 * PLAYER
 * Helper functions that are to be re-used across multiple assignments
 * and exercises.
 *
 ****************************************************************************/
#pragma once

#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include "ItemManager.h"
#include "ILoadObject.h"
#include "ISaveObject.h"
#include "ManagerBase.h"
#include "RoomManager.h"
#include "EnumParser.h"

class Player : ILoadObject, ISaveObject
{
public:
	static const int InventorySize = 10;
	
	int Id;
	std::string UserName;
	size_t HashedPassword;
	int CurrentRoomID;
	int Inventory[InventorySize];
	int EquippedSlots[InventorySize];
	int GoldPieces;
	int Mana;
	int MovePoints;
	int HitPoints;
	int Intelligence;
	int Wisdom;
	int Constitution;
	int Dexterity;
	int Strength;
	int MaxMana;
	int MaxMovePoints;
	int MaxHitPoints;
	int DamageMin;
	int DamageMax;

	Player();
	
	void TakeDamage(int Damage);
	void Die();
	bool RemoveFromInventory(int index);
	bool RemoveFromEquipped(int index);
	bool AddToInventory(int index);
	bool AddToEquipped(int index);


	Player(int in_Id);
	std::string Save() override;
	bool Load(std::vector<std::string> in_Line) override;
	bool LoadLogin(std::vector<std::string> in_Line);
	size_t GetInventoryCount();
};

inline size_t Player::GetInventoryCount()
{
	size_t retVal = 0;
	
	for(int i = 0 ; i < InventorySize; i++)	
		if (Inventory[i] != 0)
			++retVal;
	
	return retVal;
}
