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
	Item<T> getAt(int pos) const throw(...);
	void getAll(Item<T> arr[], int cap) throw(...);
	Item<T> extractAt(int pos) throw(...);
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
inline Item<T> Bin<T>::extractAt(int pos) throw(...)
{
	if (pos < 0 || mNrOfItems - 1 < pos)
		throw "Position outside of range";
	Item<T> temp = mItems.getAt(pos);
	mItems.removeAt(pos);
	mSpaceLeft += temp.getValue();
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
	if (mSpaceLeft - item.getValue() >= 0)
	{
		insertSuccess = true;
		mItems.insertAt(pos, item);
		mNrOfItems++;
		mSpaceLeft -= item.getValue();
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
	if (mSpaceLeft - item.getValue() >= 0)
	{
		insertSuccess = true;
		int iWalker = 0;
		Item<T>* arr = new Item<T>[mItems.length()];
		mItems.getAll(arr, mItems.length());
		while (arr[iWalker] < item.getValue())
			iWalker++;

		mItems.insertAt(iWalker, item);
		mNrOfItems++;
		mSpaceLeft -= item.getValue();
		delete[]arr;
	}
	return insertSuccess;
}

template<typename T>
inline Item<T> Bin<T>::getAt(int pos) const throw(...)
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


