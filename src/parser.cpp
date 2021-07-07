#include "parser.h"
#include <fstream>
#include <iostream>
#include <bitset>
#include <cstring>
#include "reader.h"
#include "writer.h"

Player::Player()
{
	
};

Player::~Player()
{

};

void Player::LoadSaveFile(const char* filepath)
{
	std::ifstream SaveFile;
	SaveFile.open(filepath, std::ios_base::binary);
	Reader r(&SaveFile, &data);

	data.DataLength = r.ReadInt();
	data.CharacterVersion = r.ReadInt();
	data.Kills = r.ReadInt();  
	data.Deaths = r.ReadInt();
	data.Crafts = r.ReadInt();
	data.Builds = r.ReadInt();
	data.NumberOfWorlds = r.ReadInt();

	data.WorldInfo = new World[data.NumberOfWorlds];

	for(int i = 0; i < data.NumberOfWorlds; i++)
	{
		World tmp;
		tmp.WorldId = r.ReadLL();
		tmp.BoolDeathPoint = r.ReadChar();
		tmp.SpawnPoint = r.ReadVec();
		tmp.BoolLogoutPoint = r.ReadChar();
		tmp.LogoutPoint = r.ReadVec();
		tmp.BoolDeathPoint = r.ReadChar();
		tmp.DeathPoint = r.ReadVec();
		tmp.HomePoint = r.ReadVec();

		tmp.bHasMoreMapData = r.ReadChar();
		if(tmp.bHasMoreMapData)
			tmp.MapData = r.ReadLongString(&tmp.MapDataLength);
		
		data.WorldInfo[i] = tmp;
	}
	
	data.Name = r.ReadString();
	data.CharacterId = r.ReadLL();
	data.StartSeed = r.ReadString();
	
	if(!(r.ReadChar()))
	{
		SaveFile.close();
		std::cout << "Data end!\n";
		return;
	}
	

	data.AdditionalDataLength = r.ReadInt();
	data.DataVersion = r.ReadInt();
	data.MaxHP = r.ReadFloat();
	data.CurrentHP = r.ReadFloat();
	data.Stamina = r.ReadFloat();
	data.BoolFirstSpawn = r.ReadChar();
	data.TimeSinceDeath = r.ReadFloat();
	data.GuardianPower = r.ReadString();
	data.GuardianCooldown = r.ReadFloat();

	data.InventoryVersion = r.ReadInt();
	data.NumberOfItems = r.ReadInt();
	data.Inventory = new Item[data.NumberOfItems];

	for(int i = 0; i < data.NumberOfItems; i++)
	{
		data.Inventory[i].Name = r.ReadString();
		data.Inventory[i].Stack = r.ReadInt();
		data.Inventory[i].Durability = r.ReadFloat();
		data.Inventory[i].posX = r.ReadInt();
		data.Inventory[i].posY = r.ReadInt();
		data.Inventory[i].BoolEquipped = r.ReadChar();
		data.Inventory[i].Quality = r.ReadInt();
		data.Inventory[i].Variant = r.ReadInt();
		data.Inventory[i].CrafterID = r.ReadLL();
		data.Inventory[i].Crafter = r.ReadString();
		//for gui only
		data.Inventory[i].Type = GetItemType(data.Inventory[i].Name);
		data.Inventory[i].MaxStack = GetMaxStackSize(data.Inventory[i].Type);
	}

	data.NoRecipes = r.ReadInt();
	data.Recipes = new std::string[data.NoRecipes];
	for(int i = 0; i < data.NoRecipes; i++)
		data.Recipes[i] = r.ReadString();
	
	data.NoStations = r.ReadInt();
	data.Stations = new Station[data.NoStations];
	for(int i = 0; i < data.NoStations; i++)
	{
		data.Stations[i].Name = r.ReadString();
		data.Stations[i].Id = r.ReadInt();
	}

	data.NoKnownMaterials = r.ReadInt();
	data.KnownMaterials = new std::string[data.NoKnownMaterials];
	for(int i = 0; i < data.NoKnownMaterials; i++)
		data.KnownMaterials[i] = r.ReadString();

	data.NoTutorials = r.ReadInt();
	data.Tutorials = new std::string[data.NoTutorials];
	for(int i = 0; i < data.NoTutorials; i++)
		data.Tutorials[i] = r.ReadString();

	data.NoUniques = r.ReadInt();
	data.Uniques = new std::string[data.NoUniques];
	for(int i = 0; i < data.NoUniques; i++)
		data.Uniques[i] = r.ReadString();
	
	data.NoTrophies = r.ReadInt();
	data.Trophies = new std::string[data.NoTrophies];
	for(int i = 0; i < data.NoTrophies; i++)
		data.Trophies[i] = r.ReadString();

	data.NoBiomes = r.ReadInt();
	data.Biomes = new int[data.NoBiomes];
	for(int i = 0; i < data.NoBiomes; i++)
		data.Biomes[i] = r.ReadInt();

	data.NoTexts = r.ReadInt();
	data.Texts = new Txt[data.NoTexts];
	for(int i = 0; i < data.NoTexts; i++)
	{
		data.Texts[i].One = r.ReadString();	
		data.Texts[i].Two = r.ReadString();	
	}

	data.Beard = r.ReadString();
	data.Hair = r.ReadString();
	data.SkinColor = r.ReadVec();
	data.HairColor = r.ReadVec();
	data.Gender = r.ReadInt();

	data.NoConsumedFoods = r.ReadInt();
	data.ConsumedFoods = new Food[data.NoConsumedFoods];
	for(int i = 0; i < data.NoConsumedFoods; i++)
	{
		data.ConsumedFoods[i].Name = r.ReadString();
		data.ConsumedFoods[i].HpLeft = r.ReadFloat();
		data.ConsumedFoods[i].StaminaLeft = r.ReadFloat();
	}

	data.SkillsVersion = r.ReadInt();
	data.NoSkills = r.ReadInt();
	data.Skills = new Skill[data.NoSkills];
	for(int i = 0; i < data.NoSkills; i++)
	{
		data.Skills[i].NameInt = r.ReadInt();
		data.Skills[i].Level = r.ReadFloat();
		data.Skills[i].Rest = r.ReadFloat();
	}

	SaveFile.close();
};


void Player::SaveFile(const char* filename)
{
	std::ofstream SaveFile;
	SaveFile.open(filename, std::ofstream::binary);
	Writer w(&SaveFile, &data);

	w.WriteInt(data.DataLength);
	w.WriteInt(data.CharacterVersion);
	w.WriteInt(data.Kills);
	w.WriteInt(data.Deaths);
	w.WriteInt(data.Crafts);
	w.WriteInt(data.Builds);
	w.WriteInt(data.NumberOfWorlds);

	for(int i = 0; i < data.NumberOfWorlds; i++)
	{
		w.WriteLL(data.WorldInfo[i].WorldId);
		w.WriteChar(data.WorldInfo[i].BoolSpawnPoint);
		w.WriteVec(data.WorldInfo[i].SpawnPoint);
		w.WriteChar(data.WorldInfo[i].BoolLogoutPoint);
		w.WriteVec(data.WorldInfo[i].LogoutPoint);
		w.WriteChar(data.WorldInfo[i].BoolDeathPoint);
		w.WriteVec(data.WorldInfo[i].DeathPoint);
		w.WriteVec(data.WorldInfo[i].HomePoint);
		
		w.WriteChar(data.WorldInfo[i].bHasMoreMapData);
		if(data.WorldInfo[i].bHasMoreMapData)
			w.WriteLongString(data.WorldInfo[i].MapData, data.WorldInfo[i].MapDataLength);
	}

	w.WriteString(data.Name);
	w.WriteLL(data.CharacterId);
	w.WriteString(data.StartSeed);
	//aditional char for more data
	w.WriteChar(1);

	w.WriteInt(data.AdditionalDataLength);
	w.WriteInt(data.DataVersion);
	w.WriteFloat(data.MaxHP);
	w.WriteFloat(data.CurrentHP);
	w.WriteFloat(data.Stamina);
	w.WriteChar(data.BoolFirstSpawn);
	w.WriteFloat(data.TimeSinceDeath);
	w.WriteString(data.GuardianPower);
	w.WriteFloat(data.GuardianCooldown);
	w.WriteInt(data.InventoryVersion);
	w.WriteInt(data.NumberOfItems);
	
	for(int i = 0; i < data.NumberOfItems; i++)
	{
		w.WriteString(data.Inventory[i].Name);
		w.WriteInt(data.Inventory[i].Stack);
		w.WriteFloat(data.Inventory[i].Durability);
		w.WriteInt(data.Inventory[i].posX);
		w.WriteInt(data.Inventory[i].posY);
		w.WriteChar(data.Inventory[i].BoolEquipped);
		w.WriteInt(data.Inventory[i].Quality);
		w.WriteInt(data.Inventory[i].Variant);
		w.WriteLL(data.Inventory[i].CrafterID);
		w.WriteString(data.Inventory[i].Crafter);
	}

	w.WriteInt(data.NoRecipes);
	for(int i = 0; i < data.NoRecipes; i++)
		w.WriteString(data.Recipes[i]);	

	w.WriteInt(data.NoStations);
	for(int i = 0; i < data.NoStations; i++)
	{
		w.WriteString(data.Stations[i].Name);
		w.WriteInt(data.Stations[i].Id);
	}
	
	w.WriteInt(data.NoKnownMaterials);
	for(int i = 0; i < data.NoKnownMaterials; i++)
		w.WriteString(data.KnownMaterials[i]);

	w.WriteInt(data.NoTutorials);
	for(int i = 0; i < data.NoTutorials; i++)
		w.WriteString(data.Tutorials[i]);

	w.WriteInt(data.NoUniques);
	for(int i = 0; i < data.NoUniques; i++)
		w.WriteString(data.Uniques[i]);

	w.WriteInt(data.NoTrophies);
	for(int i = 0; i < data.NoTrophies; i++)
		w.WriteString(data.Trophies[i]);
	
	w.WriteInt(data.NoBiomes);
	for(int i = 0; i < data.NoBiomes; i++)
		w.WriteInt(data.Biomes[i]);
	
	w.WriteInt(data.NoTexts);
	for(int i = 0; i < data.NoTexts; i++)
	{
		w.WriteString(data.Texts[i].One);	
		w.WriteString(data.Texts[i].Two);	
	}

	w.WriteString(data.Beard);
	w.WriteString(data.Hair);
	w.WriteVec(data.SkinColor);
	w.WriteVec(data.HairColor);
	w.WriteInt(data.Gender);

	w.WriteInt(data.NoConsumedFoods);
	for(int i = 0; i < data.NoConsumedFoods; i++)
	{
		w.WriteString(data.ConsumedFoods[i].Name);
		w.WriteFloat(data.ConsumedFoods[i].HpLeft);
		w.WriteFloat(data.ConsumedFoods[i].StaminaLeft);
	}

	w.WriteInt(data.SkillsVersion);
	w.WriteInt(data.NoSkills);
	for(int i = 0; i < data.NoSkills; i++)
	{
		w.WriteInt(data.Skills[i].NameInt);
		w.WriteFloat(data.Skills[i].Level);
		w.WriteFloat(data.Skills[i].Rest);
	}
	
	for(int i = 0; i < 69; i++)
	{
		char ttt = bottom[i];
		SaveFile.write(&ttt, sizeof(char));
	}

	SaveFile.close();
};


void Player::UpdateDataLength()
{
	//data.DataLength
	int d = 0;
	d += sizeof(int);
	d += sizeof(int);
	d += sizeof(int);
	d += sizeof(int);
	d += sizeof(int);
	d += sizeof(int);
	for(int i = 0; i < data.NumberOfWorlds; i++)
	{
		d += sizeof(long long);
		d += sizeof(char);
		d += sizeof(float) * 3;
		d += sizeof(char);
		d += sizeof(float) * 3;
		d += sizeof(char);
		d += sizeof(float) * 3;
		d += sizeof(float) * 3;
		d += sizeof(char);
		if(data.WorldInfo[i].bHasMoreMapData)
		{
			d += sizeof(int);
			d += data.WorldInfo[i].MapDataLength;
		}
	}

	d += data.Name.length() + 1;
	d += sizeof(long long);
	d += data.StartSeed.length() + 1;
	d += sizeof(char);
	d += sizeof(int);

	//data.additionaldata length
	int l = 0;	
	l += sizeof(data.DataVersion);
	l += sizeof(data.MaxHP);
	l += sizeof(data.CurrentHP);
	l += sizeof(data.Stamina);
	l += sizeof(data.BoolFirstSpawn);
	l += sizeof(data.TimeSinceDeath);
	l += data.GuardianPower.length() + 1;
	l += sizeof(data.GuardianCooldown);
	l += sizeof(data.InventoryVersion);
	l += sizeof(data.NumberOfItems);
	for(int i = 0; i < data.NumberOfItems; i++)
		{
			l += data.Inventory[i].Name.length() + 1;
			l += sizeof(int);
			l += sizeof(float);
			l += sizeof(int);
			l += sizeof(int);
			l += sizeof(char);
			l += sizeof(int);
			l += sizeof(int);
			l += sizeof(long long);
			l += data.Inventory[i].Crafter.length() + 1;
		}

	l += sizeof(data.NoRecipes);
	for(int i = 0; i < data.NoRecipes; i++)
		l += data.Recipes[i].length() + 1;

	l += sizeof(data.NoStations);
	for(int i = 0; i < data.NoStations; i++)
	{
		l += data.Stations[i].Name.length() + 1;
		l += sizeof(int);
	}

	l += sizeof(data.NoKnownMaterials);
	for(int i = 0; i < data.NoKnownMaterials; i++)
		l += data.KnownMaterials[i].length() + 1; 	

	l += sizeof(data.NoTutorials);
	for(int i = 0; i < data.NoTutorials; i++)
		l += data.Tutorials[i].length() + 1;

	l += sizeof(data.NoUniques);
	for(int i = 0; i < data.NoUniques; i++)
		l += data.Uniques[i].length() + 1;

	l += sizeof(data.NoTrophies);
	for(int i = 0; i < data.NoTrophies; i++)
		l += data.Trophies[i].length() + 1;

	l += sizeof(data.NoBiomes);
	for(int i = 0; i < data.NoBiomes; i++)
		l += sizeof(int);

	l += sizeof(data.NoTexts);
	for(int i = 0; i < data.NoTexts; i++)
	{
		l += data.Texts[i].One.length() + 1;
		l += data.Texts[i].Two.length() + 1;
	}

	l += data.Beard.length() + 1;
	l += data.Hair.length() + 1;
	l += sizeof(float) * 3;
	l += sizeof(float) * 3;
	l += sizeof(int);

	l += sizeof(data.NoConsumedFoods);
	for(int i = 0; i < data.NoConsumedFoods; i++)
	{
		l += data.ConsumedFoods[i].Name.length() + 1;	
		l += sizeof(float);
		l += sizeof(float);
	}

	l += sizeof(int);
	l += sizeof(data.NoSkills);
	for(int i = 0; i < data.NoSkills; i++)
	{
		l += sizeof(int);
		l += sizeof(float);
		l += sizeof(float);
	}

	data.AdditionalDataLength = l;
	data.DataLength = d + l;
};

int Player::GetItemType(const std::string& str)
{
	std::string tmp = str;
	for(unsigned int i = 0; i < tmp.length(); i++)
		tmp[i] = std::tolower(tmp[i]);

	std::string weapons[] = {"sword", "axe", "club", "mace", "torch","sledge", "knife",
							 "atgeir", "spear", "bow"};
	std::string armors[] = {"helmet", "armor", "cape"};

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


	return 0;
};

int Player::GetMaxStackSize(int type)
{
	switch(type)
	{
		case vse::WEAPON:
		case vse::SHIELD:
		case vse::ARMOR:
		case vse::TOOL:
		case vse::STATION:
			return 1;
		case vse::ARROW:
		case vse::SEED:
			return 100;
		default:
			return 0;
	}
	return 0;
};
