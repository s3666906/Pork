/******************************************************************************
 *
 * Jarryd Semmens					PORKGAME						COSC2140
 *
 * Main game engine
 *
 *****************************************************************************/
#include "PorkGame.h"

PorkGame::PorkGame()
{
	Players = std::make_unique<PlayerManager>();

	Items = std::make_unique<ItemManager>();
	Rooms = std::make_unique<RoomManager>();
	Doors = std::make_unique<DoorManager>();
	Areas = std::make_unique<AreaManager>();

	RoomStates = std::make_unique<RoomStateManager>();
}

PorkGame& PorkGame::GetInstance()
{
	static PorkGame instance;
	return instance;
}

void PorkGame::Run()
{
	std::cout << "***** Pork v" << ApplicationVersionMajor << "." << ApplicaitonVersionMinor << " *****";
	std::cout << std::endl;

	Players->LoadFromContent();

	while(!Login())
	{
		if (!GameOn)
			return;
	}

	LoadContent();
	Initialize();

	Look();

	while (GameOn)
	{
		Update();
		Render();
		Input();
	}
}

void PorkGame::LoadContent()
{
	Items->LoadFromContent();
	Rooms->LoadFromContent();
	Doors->LoadFromContent();
	Areas->LoadFromContent();
	Players->LoadFromSave();

	RoomStates->LoadContent(Players->AllPlayersCollection[Players->GetCurrentPlayerId()]->UserName);
	Doors->LoadContent(Players->AllPlayersCollection[Players->GetCurrentPlayerId()]->UserName);

	if (!RoomStates->LoadFromSave())
	{
		RoomStates->LoadFromContent();
		AddRandomItems();
	}

	if (!Doors->LoadFromSave())
		Doors->LoadFromContent();
}

void PorkGame::Initialize()
{
	//Set the starting room
	if (Players->AllPlayersCollection[Players->GetCurrentPlayerId()]->CurrentRoomID == -1)
		Rooms->SetCurrentRoom(1);
	else
		Rooms->SetCurrentRoom(Players->AllPlayersCollection[Players->GetCurrentPlayerId()]->CurrentRoomID);

	//Set the starting Area
	Areas->SetCurrentArea(Rooms->RoomCollection[Rooms->CurrentRoomId]->AreaId);
}

void PorkGame::Update()
{
}

void PorkGame::Render()
{
	std::cout << "\n> ";
}

void PorkGame::AddRandomItems()
{
	//Scramble item room locations
	const int RandomItemCount = 10;
	std::time_t nowTime = std::time(nullptr);
	boost::random::mt19937 random{static_cast<std::uint32_t>(nowTime)};

	boost::random::uniform_int_distribution<int> roomCount(1, RoomStates->RoomStateCollection.size());
	boost::random::uniform_int_distribution<int> itemCount(1, Items->ItemCollection.size());

	//We need some random items as well
	for (int i = 0; i < RandomItemCount; i++)
	{
		int randomRoom = roomCount(random);
		int randomItem = itemCount(random);

		RoomStates->RoomStateCollection[randomRoom]->Pickups.push_back(Items->ItemCollection[randomItem]->Id);
	}
}

bool PorkGame::Login()
{
	std::cout << "\nEnter Username:\n>";

	std::string userName;
	std::getline(std::cin, userName);

	std::cout << "\nEnter Password:\n>";

	std::string password;
	std::getline(std::cin, password);

	auto playerItr = Players->AllPlayersCollection.begin();
		
	if (boost::iequals(EnumParser::GetInstance().EnumToString(UserCommands::QUIT), userName))
		Quit();

	while (playerItr != Players->AllPlayersCollection.end())
	{
		//Found a possible username
		if (boost::iequals(playerItr->second->UserName, userName))
			break;

		++playerItr;
	}

	auto hashedPassword = StringHasher(password);
	if (playerItr == Players->AllPlayersCollection.end())
	{
		std::cout << "Username not found. Please try again.\n";
		return false;
	}

	if (playerItr->second->HashedPassword != hashedPassword)
	{
		//std::cout << "\n" << std::to_string( hashedPassword); //Needed to peek logins for content
		std::cout << "\nIncorrect password. Please try again.\n";
		return false;
	}

	Players->SetCurrentPlayer(playerItr->first);
	
	return true;
}

void PorkGame::Input()
{
	std::string msg;
	std::getline(std::cin, msg);

	StringHelper::GetInstance().SanitizeString(msg);
	Parse(msg);
}

bool PorkGame::Parse(std::string in_Line)
{
	if (in_Line.empty())
	{
		std::cout << "I beg your pardon?";
		return false;
	}

	//Get the first word
	std::vector<std::string> words;
	split(words, in_Line, boost::is_any_of(" "));

	UserCommands command;

	if (!EnumParser::GetInstance().TryParse(words[0], command))
	{
		std::cout << "I don't know the word \"" << words[0] << "\".";
		return false;
	}

	size_t start = words[0].length() + 1;
	size_t len = in_Line.length() - start;
	std::string commandParameters = "";

	//No parameters specified?
	if (words[0].length() < in_Line.length())
	{
		commandParameters = in_Line.substr(start, len);
		boost::to_upper(commandParameters);
	}

	switch (command)
	{
	case PICKUP:
		return Pickup(commandParameters);

	case WEAR:
		return Wear(commandParameters);

	case REMOVE:
		return Remove(commandParameters);

	case DROP:
		return Drop(commandParameters);

	case SAVE:
		return Save(commandParameters);

	case LOOK:
		Look();
		return true;

	case EXITS:
		DisplayExits();
		return true;

	case AREAS:
		DisplayAllAreas();
		return true;

	case AREA:
		DisplayCurrentArea();
		return true;

	case MOVE:
		if (!Move(commandParameters))
			return false;

		Look();
		return true;

	case OPEN:
		return SetDoorState(commandParameters, true);

	case CLOSE:
		return SetDoorState(commandParameters, false);

	case QUIT:
		Quit();
		return true;

	default:
		return false;
	}
}


bool PorkGame::Pickup(std::string in_Input)
{
	if (in_Input.empty())
	{
		std::cout << "What did you want to grab?\n";
		return false;
	}

	//Find the item
	int itemCount = RoomStates->RoomStateCollection[Rooms->CurrentRoomId]->Pickups.size();

	if (itemCount == 0)
	{
		std::cout << "There is nothing here!\n";
		return false;
	}

	auto roomItemItr = RoomStates->RoomStateCollection[Rooms->CurrentRoomId]->Pickups.begin();
	while (roomItemItr != RoomStates->RoomStateCollection[Rooms->CurrentRoomId]->Pickups.end())
	{
		if (boost::iequals(in_Input, Items->ItemCollection[*roomItemItr]->Name))
			break;

		++roomItemItr;
	}

	if (roomItemItr == RoomStates->RoomStateCollection[Rooms->CurrentRoomId]->Pickups.end())
	{
		std::cout << "That item isn't here.\n";
		return false;
	}

	//Rooms->RoomCollection[Rooms->CurrentRoomId]->

	for (int i = 0; i < Player::InventorySize; i++)
	{
		if (Players->AllPlayersCollection[Players->GetCurrentPlayerId()]->Inventory[i] != 0)
			continue;

		Players->AllPlayersCollection[Players->GetCurrentPlayerId()]->Inventory[i] = *roomItemItr;
		RoomStates->RoomStateCollection[Rooms->CurrentRoomId]->Pickups.erase(roomItemItr);


		std::cout << Items->ItemCollection[Players->AllPlayersCollection[Players->GetCurrentPlayerId()]->Inventory[i]]->Name << " added to inventory.\n";
		return true;
	}

	std::cout << "Your inventory is full!\n";
	return false;
}

bool PorkGame::Drop(std::string in_Input)
{
	if (in_Input.empty())
	{
		std::cout << "What did you want to drop?\n";
		return false;
	}

	for (int i = 0; i < Player::InventorySize; i++)
	{
		if (Players->AllPlayersCollection[Players->GetCurrentPlayerId()]->Inventory[i] == 0)
			continue;

		//Found an item
		if (boost::iequals(in_Input, Items->ItemCollection[Players->AllPlayersCollection[Players->GetCurrentPlayerId()]->Inventory[i]]->Name))
		{
			RoomStates->RoomStateCollection[Rooms->CurrentRoomId]->Pickups.push_back(
				Players->AllPlayersCollection[Players->GetCurrentPlayerId()]->Inventory[i]);
			
			Players->AllPlayersCollection[Players->GetCurrentPlayerId()]->Inventory[i] = 0;
			std::cout << "Dropped item from inventory\n";
			return true;
		}
	}

	for (int i = 0; i < Player::InventorySize; i++)
	{
		if (Players->AllPlayersCollection[Players->GetCurrentPlayerId()]->EquippedSlots[i] == 0)
			continue;

		//Found an armor
		if (boost::iequals(in_Input, Items->ItemCollection[Players->AllPlayersCollection[Players->GetCurrentPlayerId()]->EquippedSlots[i]]->Name))
		{
			std::cout << "Cannot drop " << Items->ItemCollection[Players->AllPlayersCollection[Players->GetCurrentPlayerId()]->EquippedSlots[i]]->Name <<
				", you are wearing it.\n";
			return false;
		}
	}

	std::cout << "You don't have that.\n";
	return false;
}

bool PorkGame::Wear(std::string in_Input)
{
	if (in_Input.empty())
	{
		std::cout << "What did you want to wear?\n";
		return false;
	}

	for (int i = 0; i < Player::InventorySize; i++)
	{
		if (Players->AllPlayersCollection[Players->GetCurrentPlayerId()]->Inventory[i] == 0)
			continue;

		//Found something to wear
		if (boost::iequals(in_Input, Items->ItemCollection[Players->AllPlayersCollection[Players->GetCurrentPlayerId()]->Inventory[i]]->Name))
		{
			WearPosition wearIndex = Items->ItemCollection[Players->AllPlayersCollection[Players->GetCurrentPlayerId()]->Inventory[i]]->EquipPosition;

			if (Players->AllPlayersCollection[Players->GetCurrentPlayerId()]->EquippedSlots[wearIndex] != 0)
			{
				std::cout << EnumParser::GetInstance().EnumToString(wearIndex) <<
					" slot already has something equipped\n";
				return false;
			}

			Players->AllPlayersCollection[Players->GetCurrentPlayerId()]->EquippedSlots[wearIndex] = Players->AllPlayersCollection[Players->GetCurrentPlayerId()]->Inventory[i];
			Players->AllPlayersCollection[Players->GetCurrentPlayerId()]->Inventory[i] = 0;
			std::cout << "Equipped item from inventory!\n";
			return true;
		}
	}

	std::cout << "You don't have that.\n";
	return false;
}

bool PorkGame::Remove(std::string in_Input)
{
	if (in_Input.empty())
	{
		std::cout << "What did you want to remove?\n";
		return false;
	}

	for (int i = 0; i < Player::InventorySize; i++)
	{
		if (Players->AllPlayersCollection[Players->GetCurrentPlayerId()]->EquippedSlots[i] == 0)
			continue;

		//Found an armor
		if (boost::iequals(in_Input, Items->ItemCollection[Players->AllPlayersCollection[Players->GetCurrentPlayerId()]->EquippedSlots[i]]->Name))
		{
			Players->AllPlayersCollection[Players->GetCurrentPlayerId()]->Inventory[i] = Players->AllPlayersCollection[Players->GetCurrentPlayerId()]->EquippedSlots[i];
			Players->AllPlayersCollection[Players->GetCurrentPlayerId()]->EquippedSlots[i] = 0;


			std::cout << "Add " << Items->ItemCollection[Players->AllPlayersCollection[Players->GetCurrentPlayerId()]->Inventory[i]]->Name <<
				" to inventory.\n";

			return true;
		}
	}

	std::cout << "You don't have that.\n";
	return false;
}

void PorkGame::Look()
{
	//Room Name
	std::cout << "\n" << ((Rooms)->RoomCollection[Rooms->CurrentRoomId])->Name;
	std::cout << "\n-----------------\n";

	//Room Description.
	std::cout << Rooms->RoomCollection[Rooms->CurrentRoomId]->Description;
	std::cout << std::endl;

	//Items	
	std::vector<int>::iterator itrItems = RoomStates->RoomStateCollection[Rooms->CurrentRoomId]->Pickups.begin();

	if (itrItems != RoomStates->RoomStateCollection[Rooms->CurrentRoomId]->Pickups.end())
	{
		std::cout << "Items on Floor: ";

		while (itrItems != RoomStates->RoomStateCollection[Rooms->CurrentRoomId]->Pickups.end())
		{
			std::cout << Items->ItemCollection[*itrItems]->Name;

			++itrItems;

			if (itrItems != RoomStates->RoomStateCollection[Rooms->CurrentRoomId]->Pickups.end())
				std::cout << ", ";
		}

		std::cout << std::endl;
	}

	//doors
	DisplayExits();
}

void PorkGame::DisplayAllAreas()
{
	auto areaItr = Areas->AreaCollection.begin();
	std::cout << std::endl;

	while (areaItr != Areas->AreaCollection.end())
	{
		std::cout << std::to_string(areaItr->second.Id) << "\t" << areaItr->second.Name << std::endl;
		++areaItr;
	}
}

void PorkGame::DisplayCurrentArea()
{
	std::cout << Areas->AreaCollection[Areas->CurrentAreaId].Name;
	std::cout << "\n-----------------\n";
	std::cout << Areas->AreaCollection[Areas->CurrentAreaId].Description << std::endl;
}

void PorkGame::DisplayExits()
{
	//Doors
	int exits[4];
	int exitCount = 0;
	Doors->GetDoorsForRoom(Rooms->CurrentRoomId, exits, exitCount);

	std::cout << "exits: ";

	for (int i = 0; i < exitCount; i++)
	{
		std::cout << EnumParser::GetInstance().EnumToString(Doors->DoorCollection[exits[i]]->Location) << ": ";
		std::cout << Rooms->RoomCollection[Doors->DoorCollection[exits[i]]->ExitRoomId]->Name << " [";

		if (Doors->DoorCollection[exits[i]]->IsOpen)
			std::cout << "open";
		else
			std::cout << "closed";

		std::cout << "]";

		if (i < exitCount - 1)
			std::cout << ", ";
	}
	std::cout << std::endl;
}

bool PorkGame::Move(std::string in_Input)
{
	Direction dir;
	if (!EnumParser::GetInstance().TryParse(in_Input, dir))
	{
		std::cout << "Please move North, East, South or West\n";
		return false;
	}

	int doors[4];
	int count;
	Doors->GetDoorsForRoom(Rooms->CurrentRoomId, doors, count);

	for (int i = 0; i < count; i++)
	{
		if (Doors->DoorCollection[doors[i]]->Location == dir)
		{
			if (!Doors->DoorCollection[doors[i]]->IsOpen)
			{
				std::cout << "The door is closed\n";
				return false;
			}

			Rooms->SetCurrentRoom(Doors->DoorCollection[doors[i]]->ExitRoomId);
			Players->AllPlayersCollection[Players->GetCurrentPlayerId()]->MovePoints--;
			return true;
		}
	}

	std::cout << "You can't go that way.\n";
	return false;
}

bool PorkGame::SetDoorState(std::string in_Input, bool in_IsOpen)
{
	Direction dir;
	if (!EnumParser::GetInstance().TryParse(in_Input, dir))
	{
		std::cout << "Which door? North, East, South or West?\n";
		return false;
	}

	int doors[4];
	int count;
	Doors->GetDoorsForRoom(Rooms->CurrentRoomId, doors, count);

	for (int i = 0; i < count; i++)
	{
		if (Doors->DoorCollection[doors[i]]->Location == dir)
		{
			if (Doors->DoorCollection[doors[i]]->SetState(in_IsOpen))
			{
				if (in_IsOpen)
					std::cout << "The door is now open\n";
				else
					std::cout << "The door is now closed\n";

				return true;
			}

			if (in_IsOpen)
				std::cout << "The door was already open.\n";
			else
				std::cout << "The door was already closed.\n";
		}
	}

	return false;
}

bool PorkGame::Save(std::string in_Input)
{
	SaveType saveMode;
	if (!EnumParser::GetInstance().TryParse(in_Input, saveMode))
	{
		std::cout << "Binary or Ascii?\n";
		return false;
	}

	if (saveMode == SaveType::BINARY)
	{
		std::cout << "Binary not supported\n";		
		return false;
	}
	
	//Do we have a save directory?
	boost::filesystem::path rootSave = "save";
	boost::filesystem::path playerRoot = "save/" + Players->AllPlayersCollection[Players->GetCurrentPlayerId()]->UserName;

	//Make sure our root exists
	if (create_directory(rootSave))
		std::cout << "Save Root Directory Created" << std::endl;

	if (create_directory(playerRoot))
		std::cout << "Player Directory Created" << std::endl;

	//First we serialize the player state
	Players->AllPlayersCollection[Players->GetCurrentPlayerId()]->CurrentRoomID = Rooms->CurrentRoomId;
	if (Players->Save())
		std::cout << "Player Saved!\n";
	else
		std::cerr << "Failed to save player!\n";

	//Now we need to serialize room states (items)
	if (RoomStates->Save())
		std::cout << "Room States Saved!\n";
	else
		std::cerr << "Failed to save Room States";

	//And we save the doors
	if (Doors->Save())
		std::cout << "Door States saved!\n";
	else
		std::cerr << "Failed to save door states\n";
	
	return true;
}

void PorkGame::Quit()
{
	std::cout << "Quitting..." << std::endl;
	GameOn = false;
}
