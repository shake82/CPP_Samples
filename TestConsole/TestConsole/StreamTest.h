#include "stdafx.h"
#include <vector>
using namespace std;

namespace StreamTest
{
	//Tests
	void UserDefinedClassIOTest();
	void IteratorTest();

	//Classes
	struct Data
	{
		int id;
		string value;
	};

	ostream& operator << (ostream& os, const Data& data);

	istream& operator >> (istream& is, Data& data);

}