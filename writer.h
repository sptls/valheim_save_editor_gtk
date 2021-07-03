#ifndef WRITER_H_
#define WRITER_H_

#include <fstream>
#include "data_containers.h"

class Writer
{
	public:
		Writer();
		Writer(std::ofstream* file, PlayerData* data);
		~Writer();
		void WriteChar(char c);
		void WriteInt(int i);
		void WriteFloat(float n);
		void WriteLL(long long l);
		void WriteVec(Vec v);
		void WriteString(std::string string, char len=0);
		void WriteLongString(std::string string, int len=0);
	private:
		std::ofstream* f;
};

#endif
