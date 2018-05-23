#ifndef BINHANDELER_H
#define BINHANDELER_H
#include "Bin.h"
template<typename T>
class BinHandeler
{
private:
	Bin* mBins;
	int mNrOfBins;


public:
	BinHandeler();
	~BinHandeler();
};

#endif // !BINHANDELER_H
