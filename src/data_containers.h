#ifndef DATA_CONTAINERS_H
#define DATA_CONTAINERS_H
struct Vec
{
	float X;
	float Y;
	float Z;
};

struct World
{
	long long WorldId;

	char BoolSpawnPoint;
	Vec SpawnPoint;

	char BoolLogoutPoint;
	Vec LogoutPoint;

	char BoolDeathPoint;
	Vec DeathPoint;

	Vec HomePoint;
	int MapDataLength = 0;
	char bHasMoreMapData;
	std::string MapData;
};

struct Item
{
	std::string Name;
	int Stack;
	float Durability;
	int posX;
	int posY;
	char BoolEquipped;
	int Quality;
	int Variant;
	long long CrafterID;
	std::string Crafter;

	//for gui
	int Type;
	int MaxStack;
	std::string ItemImage;
};

struct Station
{
	std::string Name;
	int Id;
};

struct Txt
{
	std::string One;
	std::string Two;
};

struct Food
{
	std::string Name;
	float HpLeft;
	float StaminaLeft;
};

struct Skill
{
	int NameInt;
	float Level;
	float Rest;
};


//saved data sorted in order of read/write
struct PlayerData
{
	int DataLength;
	int CharacterVersion;
	int Kills;
	int Deaths;
	int Crafts;
	int Builds;
	int NumberOfWorlds;
	World* WorldInfo;
	std::string Name;
	long long CharacterId;
	std::string StartSeed;
	int AdditionalDataLength;
	int DataVersion;
	float MaxHP;
	float CurrentHP;
	float Stamina;
	char BoolFirstSpawn;
	float TimeSinceDeath;
	std::string GuardianPower;
	float GuardianCooldown;
	int InventoryVersion;
	int NumberOfItems;
	Item* Inventory;
	int NoRecipes;
	std::string* Recipes;
	int NoStations;
	Station* Stations;
	int NoKnownMaterials;
	std::string* KnownMaterials;
	int NoTutorials;
	std::string* Tutorials;
	int NoUniques;
	std::string* Uniques;
	int NoTrophies;
	std::string* Trophies;
	int NoBiomes;
	int* Biomes;
	int NoTexts;
	Txt* Texts;
	std::string Beard;
	std::string Hair;
	Vec SkinColor;
	Vec HairColor;
	int Gender;
	int NoConsumedFoods;
	Food* ConsumedFoods;
	int SkillsVersion;
	int NoSkills;
	Skill* Skills;
	std::string Bottom;
};

#endif
