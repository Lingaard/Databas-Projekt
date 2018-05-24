#ifndef BINHANDELER_H
#define BINHANDELER_H
#include "Bin.h"

template<typename T>
class BinHandeler
{
private:
	Bin* mBins;
	int mNrOfBins;

	Bin::Item* mItems;
	int mNrOfItems;
public:
	BinHandeler(int nrOfBins = 1, int nrOfItems = 20, int spaceInBin = 100);
	BinHandeler(int nrOfBins, int nrOfItems, int spaceInBins[]);
	~BinHandeler();

	void insertItemsFromArray(T elementArr[], int spaceArr[], int nrOfItems);
	void putItemsInBins();
};

#endif // !BINHANDELER_H

template<typename T>
inline BinHandeler<T>::BinHandeler(int nrOfBins, int nrOfItems, int spaceInBin)
{
	mBins = new Bin[nrOfBins];
	mNrOfBins = nrOfBins;
	mNrOfItems = nrOfItems;
	mItems = new Bin::Item[nrOfItems];

	for (int i = 0; i < mNrOfBins; i++)
	{
		mBins[i].setSpace(spaceInBin);
	}
}

template<typename T>
inline BinHandeler<T>::BinHandeler(int nrOfBins, int nrOfItems, int spaceInBins[])
{
	mBins = new Bin[nrOfBins];
	mNrOfBins = nrOfBins;
	mNrOfItems = nrOfItems;
	mItems = new Bin::Item[nrOfItems];

	for (int i = 0; i < mNrOfBins; i++)
	{
		mBins[i].setSpace(spaceInBins[i]);
	}
}

template<typename T>
inline BinHandeler<T>::~BinHandeler()
{
	delete[]mBins;
	delete[]mItems;
}

template<typename T>
inline void BinHandeler<T>::insertItemsFromArray(T elementArr[], int spaceArr[], int nrOfItems)
{
	for (int i = 0; i < nrOfItems; i++)
	{
		mItems[i] = Bin::Item(elementArr[i], spaceArr[i]);
	}
}

// Puts in Items in Bins in order of first fit decreasing with a sorted array
template<typename T>
inline void BinHandeler<T>::putItemsInBins()
{
	bool keepGoing = true;
	int dir = 1;
	int iBin = 0;

	while (keepGoing)
	{
		for(int i = 0;i<)
		dir *= -1;
	}
}



