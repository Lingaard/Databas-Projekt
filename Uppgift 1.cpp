#include <iostream>
#include <fstream>
#include <crtdbg.h>
#include "PriorityQueue.h"
#include "Operation.h"
#include "BinHandeler.h"

void readFromFile(std::string fileDir, PriorityQueue<Operation>&pq, int& nrOf);

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	PriorityQueue<Operation> pq;
	int nrOfOperations = 0;
	readFromFile("../Projektuppgiften/Operationer_1a.txt", pq, nrOfOperations);
	BinHandeler<Operation> bh(3, nrOfOperations, 660);

	int values[20] = { 0 };
	Operation ops[20];
	for (int i = 0; i < nrOfOperations; i++)
	{
		ops[i] = pq.extractMax();
		values[i] = ops[i].getTime();
	}
	bh.insertItemsFromArray(ops, values, nrOfOperations);
	bh.putItemsInBins();

	for (int j = 0; j < 3; j++)
	{
		Operation ops2[10];
		try
		{
			bh.getBin(ops2, 20, j);
		}
		catch (const char* e)
		{
			std::cout << e;
		}

		for (int i = 0; i < 10; i++)
		{
			std::cout << ops2[i].toString() << std::endl;
		}
		std::cout << std::endl;
	}



	getchar();
	return 0;
}

void readFromFile(std::string fileDir, PriorityQueue<Operation>&pq, int& nrOf)
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
		nrOf++;
	}
	file.close();
}