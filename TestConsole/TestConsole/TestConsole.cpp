// TestConsole.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "ArrayPointerTest.h"
#include "StreamTest.h"
#include "ConcurrencyTest.h"

using namespace std;

int main(int argc, char* argv[])
{
	/*
		1) Testing arrays and pointers
	ArrayPointerTest::CountCharTest();

		2) Testing Custom Vector
	ArrayPointerTest::CustomVectorTest();
	
		3) Testing Lambdas
	ArrayPointerTest::LambdaTest();
		
		4)Variadic Test
	ArrayPointerTest::VariadicTest();

		5) 
	StreamTest::UserDefinedClassIOTest();
		
		6) Iterator Test 
	StreamTest::IteratorTest();
		
		7) Concurrency Test
	ConcurrencyTest::SimpleThreadingTest();
	ConcurrencyTest::MutextProducerConsumerTest();
	ConcurrencyTest::PromiseTest();
	ConcurrencyTest::PackagedTaskTest();
	ConcurrencyTest::PackagedTaskLambdaTest();
	*/
	
	ConcurrencyTest::asyncTest();

}

