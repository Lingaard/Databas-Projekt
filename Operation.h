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
	Operation(int id, std::string sub = "", int time = 0);
	Operation();
	virtual~Operation();
	bool operator<(const Operation& other) const;
	
	int getId() const;
	std::string getSubSpeciality() const;
	int getTime() const;
	std::string toString() const;

};

#endif // !OPERATION_H
