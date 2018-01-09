
#ifndef SET_H_
#define SET_H_

#include <climits>
#include <iostream>
#include <cmath>
using namespace std;

class Set
{
	public:
		Set(int);
		int * members;
		int size;
};

Set::Set(int x)
{
	int a = x / 32;

	members = new int[a];
	size = a + 1;
}

Set operator+(Set X, int x)
{
	int a = x / 32;
	int b = x % 32;

	X.members[a] |= (1 << b);
	return(X);
}

Set operator-(Set X, int x)
{
	int a = x / 32;
	int b = x % 32;

	X.members[a] &= ~(1 << b);
	return(X);
}

Set operator/(Set X, Set Y)
{
	Set Z = Set((X.size - 1) * 32);

	for(int a = 0; a < X.size; a++)
	{
		Z.members[a] = X.members[a] & ~Y.members[a];
	}

	return(Z);
}

Set operator~(Set X)
{
	Set Z = Set((X.size - 1) * 32);

	for(int a = 0; a < X.size; a++)
	{
		Z.members[a] = ~X.members[a];
	}

	return(Z);
}

ostream& operator<<(ostream& os, const Set& X)
{
	for(int a = 0; a < X.size; a++)
	{
		for(int b = 0; b < 32; b++)
		{
			if((X.members[a] >> b) & 1)
			{
				os << (b + (32 * a)) << " ";
			}
		}
	}

	return(os);
}

#endif /* SET_H_ */
