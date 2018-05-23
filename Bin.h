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
	};

	List<Item> mItems;
	int mNrOfItems;

	int mSpaceLeft;


public:
	Bin(int space = 0);
	virtual~Bin();

	T extractAt(int pos) throw(...);
	void insertAt(T element, int value, int pos = 0) throw(...);
	T getAt(int pos) const throw(...);
	void getAll(T arr[], int cap) throw(...);

};

#endif // !BIN_H

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

template<typename T>
inline void Bin<T>::insertAt(T element, int value, int pos) throw(...)
{
	if (pos < 0 || mNrOfItems < pos)
		throw "Position outside of range";
	if (mSpaceLeft - value < 0)
		throw "Element does not fit";

	mItems.insertAt(pos, Item(element, value));
	mNrOfItems++;
	mSpaceLeft -= value;
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


