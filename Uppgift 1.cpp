#include <iostream>
#include <fstream>
#include <crtdbg.h>
#include "PriorityQueue.h"
#include "Operation.h"
#include "BinHandeler.h"

void readFromFile(std::string fileDir, PriorityQueue<Operation>&pq);

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	
	PriorityQueue<Operation> pq;

	readFromFile("../Projektuppgiften/Operationer_1a.txt", pq);



	getchar();
	return 0;
}

void readFromFile(std::string fileDir, PriorityQueue<Operation>&pq)
{
	std::ifstream file;
	file.open(fileDir);
	int id, time, pos1, pos2;
	std::string line, sub;
	//while (!file.eof())
	getline(file, line);
	while (line != "")
	{
		pos1 = line.find(",");
		pos2 = line.find(",", pos1 + 1);
		id = std::stoi(line.substr(0, pos1));
		sub = line.substr(pos1 + 1, pos2 - pos1 - 1);
		time = std::stoi(line.substr(pos2 + 1));
		pq.insert(Operation(id, sub, time));
		getline(file, line);
	}
}