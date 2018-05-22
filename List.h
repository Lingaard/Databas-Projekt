#ifndef LIST_H
#define LIST_H
template<typename T>
class List
{
private:
	class Node
	{
	public:
		T mElement;
		Node* mNext;
		Node(T element, Node* next = nullptr);
		virtual~Node();
	};

	Node* mFront;
	int mNrOfElements;

	// Help functions
	int findElementPos(const T& toFind)const;
	void freeMemory();
public:
	List();
	virtual~List();
	List(const List& other);
	List& operator=(const List& other);
	void insertAt(int pos, const T& element) throw(...);
	void removeAt(int pos) throw(...);
	bool removeElement(const T& element);
	bool findElement(const T& toFind) const;
	int length() const;
	T getAt(int pos) const throw(...);
	void getAll(T arr[], int cap) throw(...);
};


#endif // !LIST_H

template<typename T>
int List<T>::findElementPos(const T& toFind) const
{
	int pos = -1;
	Node* walker = mFront;
	
	for (int walkerPos = 0; pos == -1 && walker != nullptr; walkerPos++)
	{
		if (walker->mElement == toFind)
		{
			pos = walkerPos;
		}
		walker = walker->mNext;
	}
	return pos;
}

template<typename T>
void List<T>::freeMemory()
{
	Node* walker = mFront;
	Node* toRemove = nullptr;
	while (walker != nullptr)
	{
		toRemove = walker;
		walker = walker->mNext;
		delete toRemove;
	}
}

template<typename T>
List<T>::List()
{
	mFront = nullptr;
	mNrOfElements = 0;
}

template<typename T>
List<T>::~List()
{
	freeMemory();
}

template<typename T>
List<T>::List(const List & other)
{	
	Node* otherWalker = other.mFront;
	Node* thisWalker = nullptr;
	mNrOfElements = other.mNrOfElements;
	if (mNrOfElements == 0)
	{
		mFront = nullptr;
	}
	else
	{
		mFront = new Node(otherWalker->mElement);
		thisWalker = mFront;
		otherWalker = otherWalker->mNext;
		while (otherWalker != nullptr)
		{
			thisWalker->mNext = new Node(otherWalker->mElement);
			thisWalker = thisWalker->mNext;
			otherWalker = otherWalker->mNext;
		}
	}
}

template<typename T>
List<T> & List<T>::operator=(const List & other)
{
	if (this != &other)
	{
		freeMemory();
		Node* otherWalker = other.mFront;
		Node* thisWalker = nullptr;
		mNrOfElements = other.mNrOfElements;
		if (mNrOfElements == 0)
		{
			mFront = nullptr;
		}
		else
		{
			mFront = new Node(otherWalker->mElement);
			thisWalker = mFront;
			otherWalker = otherWalker->mNext;
			while (otherWalker != nullptr)
			{
				thisWalker->mNext = new Node(otherWalker->mElement);
				thisWalker = thisWalker->mNext;
				otherWalker = otherWalker->mNext;
			}
		}
	}
	return *this;
}

template<typename T>
void List<T>::insertAt(int pos, const T & element) throw(...)
{
	if (pos < 0 || mNrOfElements < pos)
	{
		throw "Position is outside of the lists reach.";		
	}
	if (pos == 0)
	{
		mFront = new Node(element, mFront);
	}
	else
	{
		Node* walker = mFront;									// walking to point pos
		for (int walkerPos = 1; walkerPos < pos; walkerPos++)
		{
			walker = walker->mNext;
		}
		walker->mNext = new Node(element, walker->mNext);
	}
	mNrOfElements++;		
}

template<typename T>
void List<T>::removeAt(int pos) throw(...)
{
	if (pos < 0 || mNrOfElements < pos)
	{
		throw "Position is outside of the lists reach.";		
	}
	Node* toRemove = nullptr;
	if (pos == 0)
	{
		toRemove = mFront;
		mFront = toRemove->mNext;
		delete toRemove;
	}
	else
	{
		Node* walker = mFront;									// walking to point pos
		for (int walkerPos = 1; walkerPos < pos; walkerPos++)
		{
			walker = walker->mNext;
		}
		toRemove = walker->mNext;
		walker->mNext = toRemove->mNext;
		delete toRemove;
	}
	mNrOfElements--;
}

template<typename T>
bool List<T>::removeElement(const T & element)
{
	int targetPos = findElementPos(element);
	if (targetPos != -1)
	{
		removeAt(targetPos);
	}
	return targetPos != -1;
}

template<typename T>
bool List<T>::findElement(const T & toFind) const	
{	// Somehow deleted findElementPos on the line under on the file sent in for the assignment
	return findElementPos(toFind) != -1;
}

template<typename T>
int List<T>::length() const
{
	return mNrOfElements;
}

template<typename T>
T List<T>::getAt(int pos) const throw(...)
{
	if (pos > mNrOfElements)
	{
		throw "Position is outside of the lists reach.";		
	}

	Node* walker = mFront;									// walking to point pos
	for (int walkerPos = 1; walkerPos <= pos; walkerPos++)
	{
		walker = walker->mNext;
	}
	return walker->mElement;
}

template<typename T>
void List<T>::getAll(T arr[], int cap) throw(...)
{
	if (cap < mNrOfElements)
	{
		throw "Array too small.";		
	}

	Node* walker = mFront;
	for (int i = 0; i < mNrOfElements; i++)
	{
		arr[i] = walker->mElement;
		walker = walker->mNext;
	}
}


template<typename T>
List<T>::Node::Node(T element, Node * next)
{
	mElement = element;
	mNext = next;
}

template<typename T>
List<T>::Node::~Node()
{
}
