#include "ManagerBase.h"

bool ManagerBase::LoadFromContent()
{
	return LoadFromFile(ContentPath);
}

bool ManagerBase::LoadFromSave()
{
	return LoadFromFile(UserSavePath);
}

bool ManagerBase::LoadFromFile(std::string in_Path)
{
	boost::filesystem::ifstream sourceFile;
	sourceFile.open(in_Path, std::ios::out);

	if (!sourceFile.is_open())
	{
		std::cerr << "Failed to open '" + in_Path + "'\n";
		return false;
	}

	std::string line;

	std::vector<std::string> unparsedItem;
	while (std::getline(sourceFile, line))
	{
		unparsedItem.clear();

		auto pred = boost::is_any_of("\t");
		split(unparsedItem, line, pred);

		if (line.empty())
			continue;

		ProcessLine(unparsedItem);
	}

	return true;
}
