#ifndef PRIORITYQUEUE_H
#define PRIORITYQUEUE_H

template<typename T>
class PriorityQueue
{
private:
	int mNrOfItems;
	int mItemsCap;
	T* mItemArray;

	void expand();
public:
	PriorityQueue();
	~PriorityQueue();

	void insert(T item);
	T extractMin() throw(...); 

	void printArr()const;
};
#endif // !PRIORITYQUEUE_H

template<typename T>
void PriorityQueue<T>::expand()
{
	mItemsCap *= 2;
	T* temp = new T[mItemsCap];
	for (int i = 0; i <= mNrOfItems; i++)
	{
		temp[i] = mItemArray[i];
	}

	delete[]mItemArray;
	mItemArray = temp;
}

template<typename T>
PriorityQueue<T>::PriorityQueue()
{
	mItemsCap = 32;
	mNrOfItems = 0;
	mItemArray = new T[mItemsCap];
}


template<typename T>
PriorityQueue<T>::~PriorityQueue()
{
	delete[]mItemArray;
}

template<typename T>
void PriorityQueue<T>::insert(T item)
{
	int iWalker = ++mNrOfItems;
	for ( ; iWalker > 1 && item < mItemArray[iWalker / 2]; iWalker /= 2)
	{
		mItemArray[iWalker] = mItemArray[iWalker / 2];
	}
	mItemArray[iWalker] = item;	
}

template<typename T>
T PriorityQueue<T>::extractMin() throw(...)
{
	if (mNrOfItems == 0)
	{
		throw "Queue is empty";
	}

	mItemArray[0] = mItemArray[1];
	int iWalker = 1;
	int smallest;
	bool reSortDone = false;
	while (!reSortDone)
	{
		if (iWalker * 2 + 1 < mNrOfItems) // if node has 2 children
		{
			if (mItemArray[iWalker * 2] < mItemArray[iWalker * 2 + 1]) 
				smallest = iWalker * 2;
			else
				smallest  = iWalker * 2 + 1;

			if (mItemArray[smallest] < mItemArray[mNrOfItems])
			{
				mItemArray[iWalker] = mItemArray[smallest];
				iWalker = smallest;
			}
			else
			{
				mItemArray[iWalker] = mItemArray[mNrOfItems];
				reSortDone = true;
			}

		}
		else if (iWalker * 2 < mNrOfItems) // if node has 1 child)
		{
			if (mItemArray[iWalker * 2] < mItemArray[mNrOfItems])
			{
				mItemArray[iWalker] = mItemArray[iWalker * 2];
				iWalker *= 2;		      
			}
			else
			{
				mItemArray[iWalker] = mItemArray[mNrOfItems];
				reSortDone = true;
			}
		}
		else // if node has 0 children
		{
			mItemArray[iWalker] = mItemArray[mNrOfItems];
			reSortDone = true;
		}
	}
	mNrOfItems--;
	return mItemArray[0];
}

template<typename T>
inline void PriorityQueue<T>::printArr() const
{
	for (int i = 1; i < mNrOfItems + 1; i++)
	{
		std::cout << mItemArray[i] << "\n";
	}
}