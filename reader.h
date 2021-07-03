#ifndef READER_H
#define READER_H

#include <fstream>
#include "data_containers.h"

class Reader
{
	public:
		Reader();
		Reader(std::ifstream* file, PlayerData* data);
		~Reader();
		char ReadChar();
		int ReadInt();
		float ReadFloat();
		long long ReadLL();
		Vec ReadVec();
		std::string ReadString();
		std::string ReadLongString(int* len);
	private:
		std::ifstream* f;
};

#endif
