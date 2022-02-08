#include "ItemManager.h"

ItemManager::ItemManager()
{
	ContentPath = "Content/items.txt";
}

bool ItemManager::ProcessLine(std::vector<std::string> in_Line)
{
	std::unique_ptr<Item> tmpItem = std::make_unique<Item>();

	if (!tmpItem->Load(in_Line))
		return false;

	ItemCollection[tmpItem->Id] = std::move(tmpItem);
	ItemCount++;
	return true;
}
