#include "stdafx.h"
#include "ArrayPointerTest.h"
using namespace std;

namespace ArrayPointerTest
{
	void MainTest()
	{
		//interate over array	
		for (auto x : { 1, 2, 3, 4, 5, 6, 7, 8, 9 })
		{
			cout << x << ", ";
		}
		cout << endl;

		//Modify array (auto reference type is used because without it
		//, x contains a separate copy instead of refering to an array element
		int arr1[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };

		for (auto& x : arr1)
		{
			x *= 2;
		}

		for (auto x : arr1)
		{
			cout << x << ", ";
		}

		cout << endl;

		//Referencing i through j
		int i = 5;
		int& j = i;

		i *= 5;

		cout << j << endl;
	}

	void Count_Char(char* const str, char c);
	
	void CountCharTest()
	{
		char* str = "ABCDEFGHIJKLMNOPQRSTFUVWFXYZ";

		Count_Char(str, 'F');
	}

	void Count_Char(char* const str, char c)
	{
		if (str == nullptr)
		{
			cout << "empty string\n";
			return;
		}

		char* current = str;

		int count = 0;
		for (; *current != 0; ++current)
		{
			if (*current == c)
			{
				count++;
			}
		}

		cout << "charater '" << c << "' found " << count << " times" << endl;
	}
}