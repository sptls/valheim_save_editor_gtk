#include "parser.h"


//need to add rest of the items

int Player::GetItemType(const std::string& str)
{
	std::string tmp = str;
	for(unsigned int i = 0; i < tmp.length(); i++)
		tmp[i] = std::tolower(tmp[i]);

	std::string weapons[] = {"sword", "axe", "club", "mace", "torch","sledge", "knife",
							 "atgeir", "spear", "bow"};
	std::string armors[] = {"helmet", "armor", "cape"};

	if(tmp.find("pickaxe") != std::string::npos)
		return vse::TOOL;
	if(tmp.find("trophy") != std::string::npos)
		return vse::TROPHY;

	for(int i = 0; i < 10; i++)
	{
		if(tmp.find(weapons[i]) != std::string::npos)
			return vse::WEAPON;
	}

	for(int i = 0; i < 3; i++)
	{
		if(tmp.find(armors[i]) != std::string::npos)
			return vse::ARMOR;
	}

	if(tmp.find("shield") != std::string::npos)
		return vse::SHIELD;
	if(tmp.find("arrow") != std::string::npos)
		return vse::ARROW;


	return vse::UNKNOWN;
};
