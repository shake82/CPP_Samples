// TestConsole.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "ArrayPointerTest.h"


using namespace std;

//class MyVector
//{
//public:
//	//MyVector(int s) : size(s), elem{ new double[s] }{}
//
//	MyVector(int s)
//	{
//		if (s <= 0)
//			throw length_error("Vector -> size cannot be less than 1");
//
//		size = s;
//		elem = new double[s];
//	}
//
//	double& operator [](int i) 
//	{
//		if (i >= size)
//			throw out_of_range("Vector::operator []");
//		return elem[i];
//	}
//
//	double getSum()
//	{
//		if (size == 0)
//			return 0;
//
//		double sum = 0;
//		for (int i = 0; i < size; i++)
//		{
//			sum += this->elem[i];
//		}
//
//		return sum;
//	}
//
//	int getSize(){ return size; }
//private:
//	int size;	//size of the vectors
//	double * elem; // pointer to the first element
//};

int main(int argc, char* argv[])
{
	/*
		1) Testing arrays and pointers
	ArrayPointerTest::CountCharTest();
	*/
	ArrayPointerTest::CustomVectorTest();
	
	/*ArrayPointerTest::MyVector v(10);

	for (size_t i = 0; i < v.getSize(); i++)
	{
		cin >> v[i];
	}

	cout << v.getSum() << endl;

	try
	{
		cout << v[2] << endl;

		cout << v[20] << endl;
	}
	catch (out_of_range& oorEx)
	{
		cout <<"Exception: "<< oorEx.what() << endl;
	}

	try
	{
		ArrayPointerTest::MyVector v2(-27);
	}
	catch (length_error& lEx)
	{
		cout << "Exception: " << lEx.what() << endl;
		throw;
	}	
*/
}

