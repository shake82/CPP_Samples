
#include "stdafx.h"
#include "StreamTest.h"

namespace StreamTest
{
	void UserDefinedClassIOTest()
	{
		vector<Data> v;

		for (auto i = 0; i < 10; i++)
		{
			Data d;
			d.id = i + 1;
			d.value = 'A' + i;
			v.push_back(d);
		}

		for (auto d:v)
		{
			cout << d << endl;
		}

		cout << "enter data" << endl;

		auto inputRead = false;
		while(!inputRead)
		{
			Data data;
			if (cin >> data)
			{
				cout << "you entered: " << data << endl;
				inputRead = true;
			}
			else
			{
				cout << "bad format - try again" << endl;
				cin.clear();
			}
		}

	}


	ostream& operator << (ostream& os, const Data& data)
	{
		return os << data.id << ": " << data.value;
	}

	void setError(istream& is)
	{
		auto size = is.rdbuf()->in_avail();

		if (size > 0)
		{
			is.ignore(numeric_limits<streamsize>::max(), '\n');
		}

		is.setstate(ios_base::failbit);
	}

	istream& operator >> (istream& is, Data& data)
	{
		char c;
		bool error = false;

		if (is >> c && c == '{')
		{
			if (is >> data.id >> c && c == ',' && is >> c && c == '"')
			{
				string temp;
				is >> temp;

				int length = temp.length();

				if (length > 2 && temp.at(length - 1) == '}' && temp.at(length - 2) == '"')
				{
					data.value = temp.substr(0, length - 2);

					return is;
				}
			}
		}
		
		setError(is);
		
		return is;
	}
}