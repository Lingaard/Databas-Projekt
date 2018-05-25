#ifndef BINHANDELER_H
#define BINHANDELER_H
#include "Bin.h"
template<typename T>
class BinHandeler
{
private:
	Bin<T>* mBins;
	int mNrOfBins;

	int mNrOfItems;
	Item<T>* mItems;

	void binToItems(int iBin, int iItem); // not used
	void placeInItems(Item<T> item);
	void itemToBin(int iItem, int iBin);
	bool reAssign(int item[], int iPtr, int nrOfPtrs = 2);
public:
	BinHandeler(int nrOfBins = 1, int nrOfItems = 20, int spaceInBin = 100);
	BinHandeler(int nrOfBins, int nrOfItems, int spaceInBins[]);
	~BinHandeler();

	void insertItemsFromArray(T elementArr[], int spaceArr[], int nrOfItems);
	void putItemsInBins();
	void getBin(T element[], int cap, int iBin) throw(...);
	int getSpaceInBin(int iBin) const throw(...);
	void reAssign(int nrOfPtrs = 2);
};

#endif // !BINHANDELER_H

template<typename T>
inline void BinHandeler<T>::binToItems(int iBin, int iItem)
{
	Item<T> item = mBins[iBin].extractAt(iItem);
	int i;
	for (i = mNrOfItems++; mItems[i - 1] < item && i > 0; i--)
	{
		mItems[i] = mItems[i - 1];
	}
	mItems[i] = item;
}

template<typename T>
inline void BinHandeler<T>::placeInItems(Item<T> item)
{
	int i;
	for (i = mNrOfItems++; mItems[i - 1] < item && i > 0; i--)
	{
		mItems[i] = mItems[i - 1];
	}
	mItems[i] = item;
}

template<typename T>
inline void BinHandeler<T>::itemToBin(int iItem, int iBin)
{
	mBins[iBin].insertSort(mItems[iItem]);
	for (int i = iItem; i < mNrOfItems - 1; i++)
	{
		mItems[i] = mItems[i + 1];
	}
	mNrOfItems--;
}

template<typename T>
inline bool BinHandeler<T>::reAssign(int pos[], int iPtr, int nrOfPtrs)
{
	if (iPtr < nrOfPtrs)
	{
		for (; pos[iPtr] < mNrOfItems - 1 - (nrOfPtrs - iPtr); pos[iPtr]++)
		{
			if (reAssign(pos, iPtr + 1, nrOfPtrs))
				return true;
		}
	}
	else
	{
		int sum = 0;
		int diff = 0;
		Item<T> temp;
		for (int i = 0; i < nrOfPtrs; i++)
		{
			sum += mItems[pos[i]].getValue();
		}
		for (int iBin = 0; iBin < mNrOfBins; iBin++)
		{
			for (int iItem = 0; iItem < mBins[iBin].getNrOfItems(); iItem++)
			{
				diff = sum - mBins[iBin].getAt(iItem).getValue();
				if (diff > 0 && diff <= mBins[iBin].getSpace())
				{
					temp = mBins[iBin].extractAt(iItem);
					for (int i = nrOfPtrs-1; i > -1; i--) // going from top to avoid sending wrong item due to resorting
					{
						itemToBin(pos[i], iBin);
					}
					placeInItems(temp);
					//binToItems(iBin, iItem);
					return true;
				}
			}
		}
	}
	return false;
}

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
		element[i] = temp[i].getElement();
		
	}
	delete[]temp;
}

template<typename T>
inline int BinHandeler<T>::getSpaceInBin(int iBin) const throw(...)
{
	if (iBin < 0 || mNrOfBins <= iBin)
		throw "Bin outside of range.";
	return mBins[iBin].getSpace();
}

template<typename T>
inline void BinHandeler<T>::reAssign(int nrOfPtrs)
{
	bool itemChanged = false;
	int* pos = new int[nrOfPtrs];
	do
	{
		for (int i = 0; i < nrOfPtrs; i++)
		{
			pos[i] = i;
		}
		itemChanged = reAssign(pos, 0, nrOfPtrs);
	} while (itemChanged);
	delete[]pos;
}



