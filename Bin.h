#ifndef BIN_H
#define BIN_H
#include "List.h"
template<typename T>
class Bin
{
private:
	class Item
	{
	public:
		T mElement;
		int mValue;
		Item();
		Item(T element, int value);
		virtual~Item();
		bool operator<(const Item& other);
		bool operator<(const int other) const;
	};

	List<Item> mItems;
	int mNrOfItems;

	int mSpaceLeft;


public:
	Bin(int space = 0);
	virtual~Bin();

	void setSpace(int space);
	int getSpace() const;
	bool isEmpty() const;
	T getAt(int pos) const throw(...);
	void getAll(T arr[], int cap) throw(...);
	T extractAt(int pos) throw(...);
	void insertAt(T element, int value, int pos = 0) throw(...);
	void insertSort(T element, int value);

};

#endif // !BIN_H

// Item functions
template<typename T>
inline Bin<T>::Item::Item()
{
	mElement = T();
	mValue = 0;
}

template<typename T>
inline Bin<T>::Item::Item(T element, int value)
{
	mElement = element;
	mValue = value;
}

template<typename T>
inline Bin<T>::Item::~Item()
{
}

template<typename T>
inline bool Bin<T>::Item::operator<(const Item & other)
{
	return mValue < other.mValue;
}

template<typename T>
inline bool Bin<T>::Item::operator<(const int other) const
{
	return mValue < other;
}

// Bin functions
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
inline void Bin<T>::insertAt(T element, int value, int pos) throw(...)
{
	if (pos < 0 || mNrOfItems < pos)
		throw "Position outside of range";

	mItems.insertAt(pos, Item(element, value));
	mNrOfItems++;
	mSpaceLeft -= value;
}

// Insert with insertionsort
template<typename T>
inline void Bin<T>::insertSort(T element, int value)
{
	int iWalker = 0;
	Item* arr = new Item[mItems.length()];
	mItems.getAll(arr, mItems.length());
	while (arr[iWalker] < value)
		iWalker++;
	mItems.insertAt(iWalker, Item(element, value));
	mNrOfItems++;
	mSpaceLeft -= value;
	delete[]arr;
}

template<typename T>
inline T Bin<T>::getAt(int pos) const throw(...)
{
	if (pos < 0 || mNrOfItems - 1 < pos)
		throw "Position outside of range";

	return mItems.getAt(pos);
}

template<typename T>
inline void Bin<T>::getAll(T arr[], int cap) throw(...)
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
inline bool Bin<T>::isEmpty() const
{
	return mNrOfItems != 0;
}


