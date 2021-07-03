#include "reader.h"
#include <iostream>

Reader::Reader()
{
	
};

Reader::Reader(std::ifstream* file, PlayerData* data)
{
	f = file;	
};

Reader::~Reader()
{
	
};

char Reader::ReadChar()
{
	char val;
	f->read(&val, sizeof(char));
	return val;
};

int Reader::ReadInt()
{
	int val;
	f->read(reinterpret_cast<char *>(&val), sizeof(int));
	return val;
};

float Reader::ReadFloat()
{
	float val;
	f->read(reinterpret_cast<char *>(&val), sizeof(float));
	return val;
};

long long Reader::ReadLL()
{
	long long val;
	f->read(reinterpret_cast<char *>(&val), sizeof(long long));
	return val;
};

Vec Reader::ReadVec()
{
	Vec val;
	f->read(reinterpret_cast<char *>(&val.X), sizeof(float));
	f->read(reinterpret_cast<char *>(&val.Y), sizeof(float));
	f->read(reinterpret_cast<char *>(&val.Z), sizeof(float));
	return val;
};

std::string Reader::ReadString()
{
	char StringLength = ReadChar();	
	std::string string = "";
	for(int i = 0; i < StringLength; i++)
	{
		char tmp;
		f->read(&tmp, sizeof(char));
		string.push_back(tmp);	
	}
	return string;
};

std::string Reader::ReadLongString(int* len)
{
	*len = ReadInt();
	std::string string = "";
	for(int i = 0; i < *len; i++)
	{
		char tmp;
		f->read(&tmp, sizeof(char));
		string.push_back(tmp);
	}
	return string;
};
