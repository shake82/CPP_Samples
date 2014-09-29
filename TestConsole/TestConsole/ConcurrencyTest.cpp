#include "stdafx.h"
#include "ConcurrencyTest.h"
#include <thread>
#include <mutex>
#include <queue>
#include <condition_variable>
#include <future>
#include <numeric>
#include <utility>
using namespace std;

namespace ConcurrencyTest
{
#pragma region Simple Threading Test
	void f(string id, int count)
	{
		for (int i = count; i > 0; i--)
		{
			string str = "T_" + id + " - "  + to_string(i) + "\n";
			cout << str;
		}
	}

	struct F
	{
		int count;
		string id;
		F(string strId, int c)
		{
			this->count = c;
			this->id = strId;
		}
		void operator()()
		{
			for (int i = count; i > 0; i--)
			{
				string str = "T_" + id + " - " + to_string(i) + "\n";
				cout << str;
			}
		}
	};

	void SimpleThreadingTest()
	{
		cout << "THREAD!!" << endl;

		
		thread t1{ f , string("1"), 20 };
		//thread t2{ f, string("2"), 20 };
		
		thread t2{ F(string("F2"), 20) };
		;
		
		t1.join();
		t2.join();
		
	}

#pragma endregion

#pragma region Mutex

	class ProducerConsumer
	{
	private:
		mutex mmutex;
		string data;
		bool ready = false;
		condition_variable mcond;
	public:
		void consumer()
		{
			cout << "consumer started" << endl;
			while (true) {
				unique_lock<mutex> lck{ mmutex }; // acquire mmutex
				mcond.wait(lck, [&]{return ready; });
				
				

				cout << "Consumer processes: " << data << endl;

				ready = false;
				lck.unlock(); //release lck
			}
		}

		void producer()
		{
			thread t{ &ProducerConsumer::consumer, this };

			while (true)
			{
				{
					lock_guard<mutex> lg{mmutex};
					cout << "Input data: ";
					cin >> data;
					ready = true;
				}
				mcond.notify_one();

			}
		}
	};

	void MutextProducerConsumerTest()
	{
		ProducerConsumer pc;
		pc.producer();
	}

#pragma endregion

#pragma region Promises
	void print_int(future<int>& future)
	{
		auto x = future.get();

		cout << "Future Value = " << x << endl;
	}

	void PromiseTest()
	{
		promise<int> prom;
		auto future = prom.get_future();

		thread t1{ print_int, std::ref(future) };

		int i = 0;
		cout << "Enter Value: ";
		cin >> i;
		prom.set_value(i);

		t1.join();
	}
#pragma endregion

#pragma region Packaged Task
	vector<double> getRandomDoubleVector(const int count)
	{
		double lower_bound = 0;
		double upper_bound = 40;
		std::uniform_real_distribution<double> unif(lower_bound, upper_bound);
		//std::default_random_engine re;
		std::random_device rd;
		std::mt19937 gen(rd());
		
		vector<double> v;
		for (size_t i = 0; i < count; i++)
		{
			//v.push_back(unif(re));
			v.push_back(unif(gen));
		}

		return v;
	}

	double accum(double* start, double* end, double init)
	{
		cout << "calculating .." << endl;
		return accumulate(start, end, init);
	}

	void PackagedTaskTest()
	{
		auto v = getRandomDoubleVector(1000);

		using Task_Type = double(double*, double*, double);

		packaged_task<Task_Type> pt0{ accum };
		packaged_task<Task_Type> pt1{ accum };

		future<double> f0 = pt0.get_future();
		future<double> f1 = pt1.get_future();

		double* first = &v[0];

		//must move packaged_task because it cannot be moved
		thread t1{ move(pt0), first, first + v.size() / 2 , 0 };
		thread t2{ move(pt1), first + v.size() / 2, first + v.size(), 0 };


		//double* first = &v[0];
		//thread t1{ move(pt0), first, first + v.size() / 2, 0 }; // star t a thread for pt0
		//thread t2{ move(pt1), first + v.size() / 2, first + v.size(), 0 }; // star t a thread for pt1

		cout << "waiting for results..." << endl;
		cout << (f0.get() + f1.get()) << endl;

		t1.join();

		t2.join();
	}
#pragma endregion

#pragma region Packaged Task Lambda
	
	void PackagedTaskLambdaTest()
	{
		auto v = getRandomDoubleVector(1000);

		using Task_Type = double(double*, double*, double);

		packaged_task<Task_Type> pt0{ [](double* start, double* end, double init)
		{
			cout << "calculating .." << endl;
			return accumulate(start, end, init);
		} };

		future<double> f0 = pt0.get_future();
		

		double* first = &v[0];

		thread t1{ move(pt0), first, first + v.size(), 0 };
		
		cout << "waiting for results..." << endl;
		cout << f0.get() << endl;

		t1.join();
	}
#pragma endregion

#pragma region async test

	void asyncTest()
	{
		auto v = getRandomDoubleVector(10000);
		double* first = &v[0];
		auto size = v.size();

		//only use async when no shared resources are available
		auto f0 = async(accum, first, first + size/4, 0);
		auto f1 = async(accum, first + size / 4, first + size / 2, 0);
		auto f2 = async(accum, first + size / 2, first + (size *3) / 4, 0);
		auto f3 = async(accum, first + (size*3) / 4, first + size, 0);

		cout << "waiting for results..." << endl;

		//cout << f0.get() << ", " << f1.get() << ", " << f2.get() << ", " << f3.get() << endl;

		cout << (f0.get() + f1.get() + f2.get() + f3.get()) << endl;

	}
#pragma endregion
}