#ifndef BIN_H
#define BIN_H

template<typename T>
class Bin
{
private:
	class Item
	{
	public:
		T element;
		int value;

		Item(T element, int value);
		virtual~Item();
		bool operator<(const Item& other);
	};

	Item** mItems;
	int mNrOfItems;
	int mCapItems;

public:
	Bin();
	~Bin();
};

#endif // !BIN_H

template<typename T>
inline Bin<T>::Item::Item(T element, int value)
{

}

template<typename T>
inline Bin<T>::Item::~Item()
{
}

template<typename T>
inline bool Bin<T>::Item::operator<(const Item & other)
{
	return false;
}

template<typename T>
inline Bin<T>::Bin()
{
}

template<typename T>
inline Bin<T>::~Bin()
{
}
