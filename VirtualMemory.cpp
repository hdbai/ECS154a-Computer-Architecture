#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <vector>
#include <cstdlib>
#include <cstdio>
#include <sstream>
using namespace std;

class Address
{
public:
	int useBit;
	string addr;
	bool is_empty;
	Address() : useBit(0), addr(" ") {

	}

};


void clockLRU(Address address[100], vector<string> v) {

	Address content[4];
	unsigned long a;
	unsigned long b;


	for (int i = 32; i < v.size(); i++) {
		a = (unsigned long)strtoul(v.at(i).c_str(), NULL, 16) & 0xfffffc00;
		for (int j = 0; j <= 31; j++) {
			b = (unsigned long)strtoul(v.at(j).c_str(), NULL, 16);
			if ((b = a) && (address[i].useBit = 1))
			{
			}
			else if ((b = a) && (address[i].useBit = 0))
				content[i].useBit = 1;
			else if ((b != a) && (address[i].useBit = 1))
				address[i].useBit = 0;
			else if ((b != a) && (address[i].useBit = 0)) //repalce happen
			{

			}
		}





	}
}
			

		



int main(int argc, char** argv)
{

	ifstream myfile("vmtest50-4.txt");
	vector<string> v;
	string fileline;
	string addr;
	Address address[100]; 
	unsigned long temp;
	/*
	string test = "9949dc00";
	temp = (unsigned int)strtol(test.c_str(), NULL, 16);
	cout <<hex<< temp << endl;
	*/
	

	if(myfile.is_open())
	{
		while (getline(myfile, fileline)) {
			v.push_back(fileline);
	}
		for (int i = 0; i < v.size(); i++) {
			address[i].addr = v.at(i);  
			temp = (unsigned long)strtoul(v.at(i).c_str(), NULL, 16) & 0xfffffc00;
			cout<<hex<< temp << endl;
		}
		
		//clockAlgo(address[100], v);
		myfile.close();
	}
	cin.get();
	return 0;

}