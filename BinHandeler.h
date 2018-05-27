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

	void placeInItems(Item<T> item);
	void itemToBin(int iItem, int iBin);
	bool reAssignRec(int pos[], int iPos, int nrOfPos = 2);
	bool trySwitch(int pos[], int nrOfPos);

public:
	BinHandeler(int nrOfBins = 1, int nrOfItems = 20, int spaceInBin = 100);
	BinHandeler(int nrOfBins, int nrOfDays, int nrOfItems, int spaceInBins[]);
	~BinHandeler();

	int getNrOfItemsInBin(int iBin) const;
	void insertItemsFromArray(T elementArr[], int spaceArr[], int nrOfItems);
	void putItemsInBins();
	void getBin(T element[], int cap, int iBin) throw(...);
	int getSpaceInBin(int iBin) const throw(...);
	void reAssignRec(int nrOfPos = 2);
	void reAssign(int nrOfPos = 2);
};

#endif // !BINHANDELER_H

template<typename T>
void BinHandeler<T>::placeInItems(Item<T> item)
{
	int i;
	for (i = mNrOfItems++; mItems[i - 1] < item && i > 0; i--)
	{
		mItems[i] = mItems[i - 1];
	}
	mItems[i] = item;
}

template<typename T>
void BinHandeler<T>::itemToBin(int iItem, int iBin)
{
	mBins[iBin].insertSort(mItems[iItem]);
	for (int i = iItem; i < mNrOfItems - 1; i++)
	{
		mItems[i] = mItems[i + 1];
	}
	mNrOfItems--;
}

template<typename T>
bool BinHandeler<T>::reAssignRec(int pos[], int iPos, int nrOfPos)
{
	// If a change occurs function returns true which stops and restarts the function.
	// Otherwise returns false and move on.
	if (iPos < nrOfPos)
	{
		for (; pos[iPos] < mNrOfItems - (nrOfPos - 1 - iPos); pos[iPos]++)
		{
			if (reAssignRec(pos, iPos + 1, nrOfPos) == true)
				return true; 
		}
	}
	else
	{
		return trySwitch(pos, nrOfPos);			
	}
	return false;
}

template<typename T>
bool BinHandeler<T>::trySwitch(int pos[], int nrOfPos)
{
	bool switchDone = false;
	int sum = 0;
	int diff = 0;
	Item<T> temp;
	Item<T>* p;
	for (int i = 0; i < nrOfPos; i++)
	{
		sum += mItems[pos[i]].getValue();
	}
	for (int iBin = 0; iBin < mNrOfBins && !switchDone; iBin++)
	{
		for (int iItem = 0; iItem < mBins[iBin].getNrOfItems(); iItem++)
		{
			diff = sum - mBins[iBin].getAt(iItem).getValue();
			if (diff > 0 && diff <= mBins[iBin].getSpace())
			{
				temp = mBins[iBin].extractAt(iItem);
				for (int i = nrOfPos - 1; i > -1; i--) // going from top to avoid sending wrong item due to resorting
				{
					itemToBin(pos[i], iBin);
				}
				placeInItems(temp);
				return true;				
			}
		}
	}
	return switchDone;
}

template<typename T>
BinHandeler<T>::BinHandeler(int nrOfBins, int nrOfItems, int spaceInBin)
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
BinHandeler<T>::BinHandeler(int nrOfBins, int nrOfDays, int nrOfItems, int spaceInBins[])
{
	mBins = new Bin<T>[nrOfBins*nrOfDays];
	mNrOfBins = nrOfBins*nrOfDays;
	mNrOfItems = nrOfItems;
	mItems = new Item<T>[nrOfItems];

	for (int i = 0; i < mNrOfBins; i++)
	{
		mBins[i].setSpace(spaceInBins[i%nrOfBins]);
	}
}

template<typename T>
BinHandeler<T>::~BinHandeler()
{
	delete[]mBins;
	delete[]mItems;
}

template<typename T>
int BinHandeler<T>::getNrOfItemsInBin(int iBin) const
{
	return mBins[iBin].getNrOfItems();
}

template<typename T>
void BinHandeler<T>::insertItemsFromArray(T elementArr[], int spaceArr[], int nrOfItems)
{
	for (int i = 0; i < nrOfItems; i++)
	{
		mItems[i] = Item<T>(elementArr[i], spaceArr[i]);
	}
}

// Puts in Items in Bins in order of first fit decreasing with a sorted array
template<typename T>
void BinHandeler<T>::putItemsInBins()
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
void BinHandeler<T>::getBin(T element[], int cap, int iBin) throw(...)
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
int BinHandeler<T>::getSpaceInBin(int iBin) const throw(...)
{
	if (iBin < 0 || mNrOfBins <= iBin)
		throw "Bin outside of range.";
	return mBins[iBin].getSpace();
}

template<typename T>
void BinHandeler<T>::reAssignRec(int nrOfPos)
{
    bool itemChanged = false;
    int* pos = new int[nrOfPos];
    do
    {
    	for (int i = 0; i < nrOfPos; i++)
    	{
    		pos[i] = i;
    	}
    	itemChanged = reAssignRec(pos, 0, nrOfPos);
    } while (itemChanged);
    delete[]pos;
}

template<typename T>
void BinHandeler<T>::reAssign(int nrOfPos)
{
	// Function made to try other options. 
	// Constantly slower than the recursive variant according to the tests.

	bool keepGoing = true;
	int* pos = new int[nrOfPos];
	for (int i = 0; i < nrOfPos; i++)
		pos[i] = i;
	int lastPos = nrOfPos - 1;
	int iPos;
	while(pos[0] < mNrOfItems-(nrOfPos-1))
	{
		for (pos[lastPos] = pos[lastPos - 1] + 1; pos[lastPos] < mNrOfItems; pos[lastPos]++)
		{
			if (trySwitch(pos, nrOfPos))
			{
				for (int i = 0; i < nrOfPos; i++)
					pos[i] = i;
				if (nrOfPos > mNrOfItems)
				{
					pos[0] = mNrOfItems;
				}
			}
		}

		pos[lastPos - 1]++;
		
		keepGoing = true;
		for (iPos = lastPos-1; iPos > 0 && keepGoing; iPos--)
		{
			if (pos[iPos] == mNrOfItems - (nrOfPos - 1 - iPos))
			{
				pos[iPos - 1]++;
				pos[iPos] = pos[iPos - 1] + 1;
			}
			else
				keepGoing = false;
		}		
		pos[lastPos] = pos[lastPos - 1] + 1;
	}
}




