#ifndef ITEM_H
#define ITEM_H
template<typename T>
class Item
{
private:
	T mElement;
	int mValue;

public:
	Item();
	Item(T element, int value);
	virtual~Item();

	T getElement() const;
	int getValue() const;
	bool operator<(const Item& other);
	bool operator<(const int other) const;
};

// Item functions
template<typename T>
inline Item<T>::Item::Item()
{
	mElement = T();
	mValue = 0;
}

template<typename T>
inline Item<T>::Item(T element, int value)
{
	mElement = element;
	mValue = value;
}

template<typename T>
inline Item<T>::~Item()
{
}

template<typename T>
inline T Item<T>::getElement() const
{
	return mElement;
}

template<typename T>
inline int Item<T>::getValue() const
{
	return mValue;
}

template<typename T>
inline bool Item<T>::operator<(const Item & other)
{
	return mValue < other.mValue;
}

template<typename T>
inline bool Item<T>::operator<(const int other) const
{
	return mValue < other;
}

#endif // !ITEM_H

