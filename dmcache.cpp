#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <vector>
#include <cstdlib>
#include <cstdio>
using namespace std;

class Address {
public:
	Address();
	int tag;
	int set;
	int dirty;
};

Address::Address() {
	tag = 0;
	set = 0;
	dirty = 0;
}

class Line {
public:
	Line();
	Address address;
	int word[8];
};

Line::Line() {
	for (int i = 0; i < 8; i++) {
		word[i] = 0;
	}
}

using std::vector;

class Memory {
public:
	Memory();
	void addToMemory(Line memset);
	bool existInMemory(int tag);
	Line getFromMemory(int tag);
	std::vector <Line> memory;
};

Memory::Memory() {

}

void Memory::addToMemory(Line memLine)
{
	bool inmemory = false;
	for (int i = 0; i < memory.size(); i++)
	{
		if (memLine.address.tag == memory.at(i).address.tag)
		{
			memory.at(i) = memLine;
			inmemory = true;
		}
	}

	if (inmemory == false)
	{
		memory.push_back(memLine);
	}

}

bool Memory::existInMemory(int tag)
{
	for (int i = 0; i < memory.size(); i++)
	{
		if (tag == memory.at(i).address.tag)
			return true;
	}
	return false;
}

Line Memory::getFromMemory(int tag)
{
	for (int i = 0; i < memory.size(); i++)
	{
		if (tag == memory.at(i).address.tag)
			return memory.at(i);
	}
}

class Cache {
public:
	Cache();
	Line lines[32];
	void write(int address, int sets, int tag, int offset, int data);
};


Cache::Cache() {

}

void Cache::write(int address, int sets, int tag, int offset, int data) {
	lines[sets].address.set = sets;
	lines[sets].address.tag = tag;
	lines[sets].word[offset] = data;
	lines[sets].address.dirty = 1;

}




int main(int argc, char** argv) {
	Cache cache;
	int emptyCheck[32];
	for (int i = 0; i < 32; i++)
		emptyCheck[i] = 0;
	Memory memory;
	std::string fileline;
	ifstream myfile(argv[1]);
	if (myfile.is_open())
	{
		while (getline(myfile, fileline)) {
			std::string addre = fileline.substr(0, 4);
			std::string words = fileline.substr(8, 2);
			std::string mode = fileline.substr(5, 2);
			unsigned int address = (unsigned int)strtol(addre.c_str(), NULL, 16);
			unsigned int sets = (address & 0xF8) >> 3;
			unsigned int tag = address >> 8;
			unsigned int offset = address & 0x7;
			unsigned int data = (unsigned int)strtol(words.c_str(), NULL, 16);

			if (mode == "FF") {
				if (emptyCheck[sets] == 0 || tag == cache.lines[sets].address.tag) {
					cache.write(address, sets, tag, offset, data);
					emptyCheck[sets] = 1;
				}
				else {
					memory.addToMemory(cache.lines[sets]);
					if (memory.existInMemory(tag))
					{
						cache.lines[sets] = memory.getFromMemory(tag);
						cache.lines[sets].word[offset] = data;
						cache.lines[sets].address.dirty = 1;
						emptyCheck[sets] = 1;
					}
					else {
						cache.write(address, sets, tag, offset, data);
						emptyCheck[sets] = 1;
					}
				}
			}
			else {

				ofstream ofile("dm-out.txt", ios::app);
				if (cache.lines[sets].address.tag == tag) {
					int dataToF = cache.lines[sets].word[offset];

					ofile << hex << uppercase << setfill('0') << setw(2) << dataToF;
					ofile << " " << 1 << " " << cache.lines[sets].address.dirty << endl;
					ofile.close();
				}
				else {
					int isDirty = cache.lines[sets].address.dirty;
					memory.addToMemory(cache.lines[sets]);
					cache.lines[sets] = memory.getFromMemory(tag);
					cache.lines[sets].address.dirty = 0;
					int dataToF = cache.lines[sets].word[offset];

					ofile << hex << uppercase << setfill('0') << setw(2) << dataToF;
					ofile << " " << 0 << " " << isDirty << endl;
					ofile.close();
				}
			}
		}
		myfile.close();
	}
	else {
		std::cout << "Can't open the file." << std::endl;
	}
	//cin.get();

	return 0;
}

