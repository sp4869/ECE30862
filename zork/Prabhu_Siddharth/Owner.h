#ifndef OWNER_H_
#define OWNER_H_
#include <string>
using namespace std;

class Owner {
public:
	Owner();
	string getOwner();
	string getObject();
	void setObject(string);
	void setOwner(string);
	void has(int);

private:
	string owner;
	string object;
	int has_object;
};

#endif