#include <cstring>
#include <iostream>
#include "data_containers.h"
#include "writer.h"

Writer::Writer()
{
	
};

Writer::Writer(std::ofstream* file, PlayerData* data)
{
	f = file;
};

Writer::~Writer()
{
	
};

void Writer::WriteChar(char c)
{
	f->write(&c, sizeof(char));	
};

void Writer::WriteInt(int i)
{
	f->write(reinterpret_cast<char *>(&i), sizeof(int));
};

void Writer::WriteFloat(float n)
{
	f->write(reinterpret_cast<char *>(&n), sizeof(float));
};

void Writer::WriteLL(long long l)
{
	f->write(reinterpret_cast<char *>(&l), sizeof(long long));
};

void Writer::WriteVec(Vec v)
{
	f->write(reinterpret_cast<char *>(&v.X), sizeof(float));	
	f->write(reinterpret_cast<char *>(&v.Y), sizeof(float));	
	f->write(reinterpret_cast<char *>(&v.Z), sizeof(float));	
};

void Writer::WriteString(std::string string, char len)
{
	if(!len)
		len = string.length();
	f->write(&len, sizeof(char));
	f->write(string.c_str(), len);
};

void Writer::WriteLongString(std::string string, int len)
{
	if(!len)
		len = string.length();
	WriteInt(len);
	f->write(string.c_str(), len);
};
