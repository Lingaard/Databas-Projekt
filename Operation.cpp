#include "Operation.h"

Operation::Operation(int id, std::string sub, int time)
{
	mId = id;
	mSubSpecialty = sub;
	mTime = time;
}

Operation::~Operation()
{
}

bool Operation::operator<(const Operation & other) const
{
	return mTime < other.mTime;
}

int Operation::getId() const
{
	return mId;
}

std::string Operation::getSubSpeciality() const
{
	return mSubSpecialty;
}

int Operation::getTime() const
{
	return mTime;
}


