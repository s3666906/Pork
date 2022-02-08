/****************************************************************************
 * Object Oriented Programming Using C++ CPT323
 * Assignment 2 - RMIT SP1 2020
 * @author Miroslav Petkovic s3666906
 * PLAYER
 * All the possible statistics of a player  
 *
 ****************************************************************************/
#include "Player.h"

Player::Player()
{
	CurrentRoomID = -1;

	UserName = "Default";

	for (int i = 0; i < InventorySize; i++)
	{
		Inventory[i] = 0;
		EquippedSlots[i] = 0;
	}

	Id = 0;
	HashedPassword = 0;
	GoldPieces = 0;
	Mana = 100;
	MovePoints = 5;
	HitPoints = 100;
	Intelligence = 10;
	Wisdom = 10;
	Constitution = 10;
	Dexterity = 10;
	Strength = 10;
}

void Player::TakeDamage(const int Damage)
{
	HitPoints -= Damage;

	if (HitPoints <= 0)	
		HitPoints = 0;	
}

void Player::Die()
{
	if (HitPoints <= 0)
	{
		std::cout << "You dead yo";
	}
}

bool Player::RemoveFromInventory(const int index)
{
	if (index < 0 || index >= InventorySize)
	{
		std::cout << "Yeah can't do that, you need more items....";
	}

	return false;
}


bool Player::RemoveFromEquipped(const int index)
{
	if (index < 0 || index >= InventorySize)
	{
		std::cout << "Yeah can't do that, you need more items....";
	}

	return false;
}

bool Player::AddToInventory(const int index)
{
	if (index > 0 || index <= InventorySize)
	{
		std::cout << "Yeah can't do that, you need more room....";
	}

	return false;
}

bool Player::AddToEquipped(const int index)
{
	if (index > 0 || index <= InventorySize)
	{
		std::cout << "Yeah can't do that, you need more appendages....";
	}

	return false;
}

std::string Player::Save()
{
	std::string result;

	//room number of where the player is
	result += std::to_string(this->CurrentRoomID) + "\t";

	//Get the equpped items
	for (int i = 0; i < InventorySize; i++)
	{
		if (EquippedSlots[i] == 0)
			result += "NULL";
		else
			result += std::to_string(EquippedSlots[i]);

		result += "\t";
	}

	//Write out inventory
	size_t invCount = this->GetInventoryCount();
	result += std::to_string(invCount) + "\t";

	for(size_t i = 0; i < invCount; i++)
		result += std::to_string(this->Inventory[i]) + "\t";		

	//Number of gold pieces held
	result += std::to_string(this->GoldPieces) + "\t";

	//Intelligence stat
	result += std::to_string(this->Intelligence) + "\t";

	//Wisdom stat
	result += std::to_string(this->Wisdom) + "\t";

	//Strength stat
	result += std::to_string(this->Strength) + "\t";

	//Dexterity stat
	result += std::to_string(this->Dexterity) + "\t";

	//Constitution stat
	result += std::to_string(this->Constitution) + "\t";

	//Hit points stat
	result += std::to_string(this->HitPoints) + "\t";

	//Mana stat
	result += std::to_string(this->Mana) + "\t";

	//Move points stat
	result += std::to_string(this->MovePoints) + "\t";

	return result;
}

bool Player::Load(std::vector<std::string> in_Line)
{
	int index = 0;
	//room number of where the player is
	CurrentRoomID = std::stoi(in_Line[index++]);

	//Get the equipped slots
	for (int i = 0; i < InventorySize; i++, index++)
	{		
		if (in_Line[index] == "NULL")
			continue;;

		EquippedSlots[i] = std::stoi(in_Line[index]);
	}

	//Count of items in inventory
	int inventoryCount = std::stoi(in_Line[index++]);
	for (int i = 0; i < inventoryCount; i++)
		Inventory[i] = std::stoi(in_Line[index++]);

	//Number of gold pieces held
	GoldPieces = std::stoi(in_Line[index++]);

	//Intelligence stat
	Intelligence = std::stoi(in_Line[index++]);

	//Wisdom stat
	Wisdom = std::stoi(in_Line[index++]);

	//Strength stat
	Strength = std::stoi(in_Line[index++]);

	//Dexterity stat
	Dexterity = std::stoi(in_Line[index++]);

	//Constitution stat
	Constitution = std::stoi(in_Line[index++]);

	//Hit points stat
	HitPoints = std::stoi(in_Line[index++]);

	//Mana stat
	Mana = std::stoi(in_Line[index++]);

	//Move points stat
	MovePoints = std::stoi(in_Line[index++]);

	return true;
}

bool Player::LoadLogin(std::vector<std::string> in_Line)
{
	//Id
	Id = std::stoi(in_Line[0]);

	//Username
	UserName = in_Line[1];
		
	//HashedPassword
	std::stringstream sstream(in_Line[2]);
	sstream >> HashedPassword;	

	return true;
}
