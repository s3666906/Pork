/****************************************************************************
 * Object Oriented Programming Using C++ CPT323
 * Assignment 2 - RMIT SP1 2020
 * @author Miroslav Petkovic s3666906
 * PLAYERMANAGER
 *
 * 
 ****************************************************************************/

#pragma once

#include <string>
#include <vector>
#include <map>
#include <iostream>

#include "Player.h"
#include "ILoadObject.h"
#include "ManagerBase.h"
#include "RoomManager.h"
#include "ItemManager.h"
#include <boost/algorithm/string.hpp>

class PlayerManager : public ManagerBase
{
protected:
    bool ProcessLine(std::vector<std::string> in_Line) override;
    int CurrentPlayerId;
	
public:  
	

	std::map< int, std::unique_ptr< Player>> AllPlayersCollection;
	
    explicit PlayerManager();
    void LoadContent(std::string in_PlayerName);
    bool Save();

    int GetCurrentPlayerId() const;
    bool SetCurrentPlayer(int in_PlayerId);

    bool LoadFromSave() override;
};

