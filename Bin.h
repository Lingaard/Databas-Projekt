#ifndef BIN_H
#define BIN_H
#include "List.h"
#include "Item.h"
template<typename T>
class Bin
{
private:


	List<Item<T>> mItems;
	int mNrOfItems;

	int mSpaceLeft;


public:
	Bin(int space = 0);
	virtual~Bin();

	void setSpace(int space);
	int getSpace() const;
	int getNrOfItems() const;
	bool isEmpty() const;
	T getAt(int pos) const throw(...);
	void getAll(Item<T> arr[], int cap) throw(...);
	T extractAt(int pos) throw(...);
	bool insertAt(T element, int value, int pos = 0) throw(...);
	bool insertAt(Item<T> item, int pos = 0) throw(...);
	bool insertSort(T element, int value);
	bool insertSort(Item<T> item);

};

#endif // !BIN_H

template<typename T>
inline Bin<T>::Bin(int space)
{
	mNrOfItems = 0;
	mSpaceLeft = space;
}

template<typename T>
inline Bin<T>::~Bin()
{
}

template<typename T>
inline T Bin<T>::extractAt(int pos) throw(...)
{
	if (pos < 0 || mNrOfItems - 1 < pos)
		throw "Position outside of range";
	T temp = mItems.getAt(pos).mElement;
	mItems.removeAt(pos);
	mNrOfItems--;
	return temp;
}

// Insert at position
template<typename T>
inline bool Bin<T>::insertAt(T element, int value, int pos) throw(...)
{
	insertAt(Item<T>(element, value, pos));
}

template<typename T>
inline bool Bin<T>::insertAt(Item<T> item, int pos) throw(...)
{
	if (pos < 0 || mNrOfItems < pos)
		throw "Position outside of range";
	
	bool insertSuccess = false;
	if (mSpaceLeft - item.mValue >= 0)
	{
		insertSuccess = true;
		mItems.insertAt(pos, item);
		mNrOfItems++;
		mSpaceLeft -= item.mValue;
	}
	return insertSuccess;
}

// Insert with insertionsort
template<typename T>
inline bool Bin<T>::insertSort(T element, int value)
{
	insertSort(Item<T>(element, value));
}

template<typename T>
inline bool Bin<T>::insertSort(Item<T> item)
{
	bool insertSuccess = false;
	if (mSpaceLeft - item.mValue >= 0)
	{
		insertSuccess = true;
		int iWalker = 0;
		Item* arr = new Item[mItems.length()];
		mItems.getAll(arr, mItems.length());
		while (arr[iWalker] < item.mValue)
			iWalker++;

		mItems.insertAt(iWalker, item);
		mNrOfItems++;
		mSpaceLeft -= item.mValue;
		delete[]arr;
	}
	return insertSuccess;
}

template<typename T>
inline T Bin<T>::getAt(int pos) const throw(...)
{
	if (pos < 0 || mNrOfItems - 1 < pos)
		throw "Position outside of range";

	return mItems.getAt(pos);
}

template<typename T>
inline void Bin<T>::getAll(Item<T> arr[], int cap) throw(...)
{
	if (cap < mNrOfItems)
		throw "Array too small.";
	
	mItems.getAll(arr, cap);
}

template<typename T>
inline void Bin<T>::setSpace(int space)
{
	mSpaceLeft = space;
}

template<typename T>
inline int Bin<T>::getSpace() const
{
	return mSpaceLeft;
}

template<typename T>
inline int Bin<T>::getNrOfItems() const
{
	return mNrOfItems;
}

template<typename T>
inline bool Bin<T>::isEmpty() const
{
	return mNrOfItems != 0;
}


