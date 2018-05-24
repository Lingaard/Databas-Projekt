#ifndef BINHANDELER_H
#define BINHANDELER_H
#include "Bin.h"
template<typename T>
class BinHandeler
{
private:
	Bin<T>* mBins;
	int mNrOfBins;

	Item<T>* mItems;
	int mNrOfItems;
public:
	BinHandeler(int nrOfBins = 1, int nrOfItems = 20, int spaceInBin = 100);
	BinHandeler(int nrOfBins, int nrOfItems, int spaceInBins[]);
	~BinHandeler();

	void insertItemsFromArray(T elementArr[], int spaceArr[], int nrOfItems);
	void putItemsInBins();
	void getBin(T element[], int cap, int iBin) throw(...);
};

#endif // !BINHANDELER_H

template<typename T>
inline BinHandeler<T>::BinHandeler(int nrOfBins, int nrOfItems, int spaceInBin)
{
	mBins = new Bin<T>[nrOfBins];
	mNrOfBins = nrOfBins;
	mNrOfItems = nrOfItems;
	mItems = new Item<T>[nrOfItems];

	for (int i = 0; i < mNrOfBins; i++)
	{
		mBins[i].setSpace(spaceInBin);
	}


}

template<typename T>
inline BinHandeler<T>::BinHandeler(int nrOfBins, int nrOfItems, int spaceInBins[])
{
	mBins = new Bin<T>[nrOfBins];
	mNrOfBins = nrOfBins;
	mNrOfItems = nrOfItems;
	mItems = new Item<T>[nrOfItems];

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
		mItems[i] = Item<T>(elementArr[i], spaceArr[i]);
	}
}

// Puts in Items in Bins in order of first fit decreasing with a sorted array
template<typename T>
inline void BinHandeler<T>::putItemsInBins()
{
	Item<T>* restItems = new Item<T>[mNrOfItems];
	int nrOfRestItems = 0;
	bool keepGoing = true;
	int dir = 1;
	int iBin = 0;
	int iItem = 0;
	int timesSkipped = 0;
	int lastEnter = 0;
	while (iItem < mNrOfItems)
	{
		for (; 0 <= iBin && iBin < mNrOfBins; iBin += dir)
		{
			// Try to place in bin. Skips bin if too large. After trying all bins skip item.
			// 
			if (mBins[iBin].insertAt(mItems[iItem], 0))
			{
				timesSkipped = 0;
				iItem++;
				lastEnter = iBin;
			}
			else
			{
				timesSkipped++;
			}
		}
		dir *= -1;
		if (timesSkipped == mNrOfBins)
		{
			restItems[nrOfRestItems++] = mItems[iItem++];
			timesSkipped = 0;
			iBin = lastEnter + dir;
		}
		else if (timesSkipped != 0)
		{
			iBin = lastEnter; 
		}
		else
		{
			iBin += dir;
		}
	}
	delete[]mItems;
	mItems = restItems;
	mNrOfItems = nrOfRestItems;

}

template<typename T>
inline void BinHandeler<T>::getBin(T element[], int cap, int iBin) throw(...)
{
	if (iBin < 0 || mNrOfBins <= iBin)
		throw "Bin outside of range.";
	if (cap < mBins[iBin].getNrOfItems())
		throw "Array too small.";

	Item<T>* temp = new Item<T>[mBins[iBin].getNrOfItems()];
	mBins[iBin].getAll(temp, mBins[iBin].getNrOfItems());


	for (int i = 0; i < mBins[iBin].getNrOfItems(); i++)
	{
		element[i] = temp[i].mElement;
		
	}
	delete[]temp;
}



