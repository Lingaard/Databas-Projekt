#include <iostream>
#include <fstream>
#include <crtdbg.h>
#include <ctime>
#include <chrono>
#include "PriorityQueue.h"
#include "Operation.h"
#include "BinHandeler.h"

void readFromFile(std::string fileDir, PriorityQueue<Operation>&pq, int& nrOf);
void test(PriorityQueue<Operation>& pq,BinHandeler<Operation>& bh, int nrOfOperations, int nrOfRooms, int nrOfDays);
void printBin(BinHandeler<Operation>& bh, int iBin, int nrOfRooms);

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	int nrOfOperations = 0;
	PriorityQueue<Operation> pq;
	readFromFile("../Projektuppgiften/Operationer_1a.txt", pq, nrOfOperations);
	BinHandeler<Operation> bh(3, nrOfOperations, 660);
	test(pq, bh, nrOfOperations, 3, 1);
	std::cout << "----------------------------------------------" << std::endl;

	readFromFile("../Projektuppgiften/Operationer_1b.txt", pq, nrOfOperations);
	BinHandeler<Operation> bh2(3, nrOfOperations, 660);
	test(pq, bh2, nrOfOperations, 3, 1);
	std::cout << "----------------------------------------------" << std::endl;

	readFromFile("../Projektuppgiften/Operationer_2.txt", pq, nrOfOperations);
	int time[3] = { 660,840,540 };
	BinHandeler<Operation> bh3(3, 2, nrOfOperations, time);
	test(pq, bh3, nrOfOperations, 3, 2);
	std::cout << "----------------------------------------------" << std::endl;



	getchar();
	return 0;
}

void readFromFile(std::string fileDir, PriorityQueue<Operation>&pq, int& nrOf)
{
	nrOf = 0;	
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

void test(PriorityQueue<Operation>& pq, BinHandeler<Operation>& bh, int nrOfOperations, int nrOfRooms, int nrOfDays)
{
	int* values = new int[nrOfOperations];
	Operation* ops = new Operation[nrOfOperations];
	int totalRooms = nrOfDays * nrOfRooms;
	for (int i = 0; i < nrOfOperations; i++)
	{
		ops[i] = pq.extractMax();
		values[i] = ops[i].getTime();
	}
	bh.insertItemsFromArray(ops, values, nrOfOperations);
	bh.putItemsInBins();

	for (int j = 0; j < totalRooms; j++)
	{
		printBin(bh, j, nrOfRooms);
	}
	std::chrono::microseconds us;
	
	std::chrono::high_resolution_clock::time_point cstart, cend;
	cstart = std::chrono::high_resolution_clock::now();
	
	for (int i = 2; i < 4; i++)
		bh.reAssign(i);
	
	//bh.reAssign(2);
	cend = std::chrono::high_resolution_clock::now();
	std::chrono::microseconds diff = std::chrono::duration_cast<std::chrono::microseconds>(cend - cstart);
									 
	std::cout << "resorting took " << diff.count() << "us" << std::endl;
	std::cout << std::endl << "Print after resorting: " << std::endl << std::endl;

	for (int j = 0; j < totalRooms; j++)
	{
		printBin(bh, j, nrOfRooms);
	}
	delete[]ops;
	delete[]values;
}

void printBin(BinHandeler<Operation>& bh, int iBin, int nrOfRooms)
{
	Operation* ops = new Operation[bh.getNrOfItemsInBin(iBin)];
	try
	{
		bh.getBin(ops, bh.getNrOfItemsInBin(iBin), iBin);
	}
	catch (const char* e)
	{
		std::cout << e;
	}
	//std::cout << iBin <<" / " <<nrOfDays <<" + 1 = "<< iBin / nrOfDays + 1 <<"  "<< iBin <<" % "<<nrOfDays <<" + 1 = "<< iBin % nrOfDays + 1 << std::endl;
	std::cout << "Room: " << iBin % nrOfRooms + 1 << " Day: " << iBin / nrOfRooms + 1 << std::endl;
	for (int i = 0; i < bh.getNrOfItemsInBin(iBin); i++)
	{
		std::cout << ops[i].toString() << std::endl;
	}

	std::cout << "Time left in room: " << bh.getSpaceInBin(iBin) << std::endl << std::endl;
	delete[]ops;
}