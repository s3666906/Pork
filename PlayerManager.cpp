/****************************************************************************
 * Object Oriented Programming Using C++ CPT323
 * Assignment 2 - RMIT SP1 2020
 * @author Miroslav Petkovic s3666906
 * PLAYERMANAGER
 * All the possible statistics of a player
 *
 ****************************************************************************/

#include "PlayerManager.h"

#include "PorkGame.h"

PlayerManager::PlayerManager()
{
    ContentPath = "Content/players.txt";
}

bool PlayerManager::ProcessLine(std::vector<std::string> in_Line)
{
    auto player = std::make_unique<Player>();    

    if(player->LoadLogin(in_Line))
    {
        AllPlayersCollection[player->Id] = std::move(player);
        return true;
    }

    return false;
}

bool PlayerManager::Save()
{	
    std::string savePath = "save/" + AllPlayersCollection[CurrentPlayerId]->UserName + "/player.txt";
    boost::filesystem::ofstream destinationFile;
    destinationFile.open(savePath);

    if (!destinationFile.is_open())
    {
        std::cerr << "Failed to open '" << savePath << "'\n";
        return false;
    }       

    destinationFile << AllPlayersCollection[CurrentPlayerId]->Save();

    return true;
}

int PlayerManager::GetCurrentPlayerId() const
{
    return CurrentPlayerId;
}

bool PlayerManager::SetCurrentPlayer(int in_PlayerId)
{
    auto playItr = AllPlayersCollection.find(in_PlayerId);

    if (playItr == AllPlayersCollection.end())
        return false;
	
    CurrentPlayerId = in_PlayerId;
    UserSavePath = "save/" + playItr->second->UserName + "/player.txt";
	
    return true;
}

bool PlayerManager::LoadFromSave()
{
    boost::filesystem::ifstream sourceFile;
    sourceFile.open(UserSavePath, std::ios::out);

    if (!sourceFile.is_open())
    {
        std::cerr << "Failed to open '" + UserSavePath + "'\n";
        return false;
    }

    std::string line;

    std::vector<std::string> unparsedItem;	
    std::getline(sourceFile, line);

    if (line.empty())
    {
        std::cerr << "Failed to read line in '" + UserSavePath + "'\n";
	    return false;
    }
	
    auto pred = boost::is_any_of("\t");
    split(unparsedItem, line, pred);

    return AllPlayersCollection[GetCurrentPlayerId()]->Load(unparsedItem);
}
