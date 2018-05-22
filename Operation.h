#ifndef OPERATION_H
#define OPERATION_H
#include <string>
class Operation
{
private:
	int mId;
	std::string mSubSpecialty;
	int mTime;

public:
	Operation(int id = 0, std::string sub = "", int time = 0);
	virtual~Operation();
	bool operator<(const Operation& other) const;
	int getId() const;
	std::string getSubSpeciality() const;
	int getTime() const;

};

#endif // !OPERATION_H
