// SimpleLinkedList.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

using namespace std;

struct MyLinkNode
{
	MyLinkNode() : nextNode(0){}
	int value;

	MyLinkNode *nextNode;
};

/*
Build list
*/
void BuildList(MyLinkNode * const parentNode)
{
	cout << "#########################" << endl;
	cout << "#### BUILD LIST MODE ####" << endl;
	cout << "#########################" << endl << endl;
	cout << "Add numbers to the linked list. Enter \"-1\" or lower to stop" << endl;

	int input = 0;

	MyLinkNode * lastNode = parentNode;

	while (lastNode->nextNode != 0)
	{
		lastNode = lastNode->nextNode;
	}

	do
	{
		if (cin >> input)
		{
			if (input < 0)
			{
				continue;
			}
			cout << "Adding number: " << input << endl;;

			lastNode->nextNode = new MyLinkNode();
			lastNode = lastNode->nextNode;
			lastNode->value = input;
		}
		else
		{
			cout << "Wrong format. Please add a valid number" << endl;
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}
	} while (input >= 0);

	cout << "Exiting Build List Mode!!\n\n";
}

void WalkList(MyLinkNode * const rootNode)
{
	cout << "#########################" << endl;
	cout << "#### Walk LIST MODE ####" << endl;
	cout << "#########################" << endl << endl;

	char mode = ' ';
	do
	{
		cout << "What do you want to do\n'l': list all\n'f': find value\n'q': quit\n";

		cin >> mode;
		switch (mode)
		{
		case 'f':
		{
			cout << "Enter value to find: ";
			int val = 0;
			while (true)
			{
				if (!(cin >> val))
				{
					cout << "Wrong format. Please add a valid number" << endl;
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
				}
				else
				{
					break;
				}
			}
			auto currentNode = rootNode;
			int index = 0;
			bool found = false;
			while (currentNode->nextNode != 0)
			{
				currentNode = currentNode->nextNode;
				if (currentNode->value == val)
				{
					found = true;
					break;
				}

				index++;
			}

			if (found)
			{
				cout << "Found at index: " << index;
			}
			else
			{
				cout << "Value not found";
			}
		}
			break;
		case 'l':
			cout << "List All Values: ";

			auto currentNode = rootNode;
			while (currentNode->nextNode != 0)
			{
				currentNode = currentNode->nextNode;
				cout << currentNode->value << ", ";
			}
			cout << endl;
			break;
		}
		cout << endl;

		//cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cin.ignore();
	} while (mode != 'q');

	cout << "Exiting Walk List Mode!!\n\n";
}


int main(int argc, char * argv[])
{
	char mode = ' ';

	//setting up the root node
	MyLinkNode * firstNode = new MyLinkNode();
	firstNode->value = -1;

	do
	{
		cout << "What do you want to do\n'b': build list\n'w': walk list\n'q': quit\n";

		cin >> mode;
		switch (mode)
		{
		case 'b':
			BuildList(firstNode);
			break;
		case 'w':
			WalkList(firstNode);
			break;
		}
		cout << endl;

		auto size = cin.rdbuf()->in_avail();

		if (size > 0)
		{
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}
	} while (mode != 'q');


}