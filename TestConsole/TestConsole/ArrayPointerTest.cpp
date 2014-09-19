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


	void outputContainer(BaseContainer& const container)
	{
		cout << "Container Output: ";
		for (int i = 0; i < container.getSize(); i++)
		{
			cout << container[i] << ",";
		}

		cout << endl;
	}

	void CustomVectorTest()
	{
		MyVector v(10);

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
			cout << "Exception: " << oorEx.what() << endl;
		}

		try
		{
			MyVector v2(-27);
		}
		catch (length_error& lEx)
		{
			cout << "Exception: " << lEx.what() << endl;
		}

		cout << "Initializing container test: ";
		MyVector v3 = {1,2,3,4,5};

		
		for (size_t i = 0; i < v3.getSize(); i++)
		{
			cout << v3[i] << ", ";
		}

		cout << endl;

		//vectorContainerTest
		Vector_Container vc = {1,2,3,4,5};
		outputContainer(vc);

		cout << "Copying v4 from v3: ";
		MyVector v4(v3);

		for (size_t i = 0; i < v4.getSize(); i++)
		{
			cout << v4[i] << ", ";
		}
		cout << endl;

		cout << "Copying v5 from v3: ";
		MyVector v5 = v3;

		for (size_t i = 0; i < v5.getSize(); i++)
		{
			cout << v5[i] << ", ";
		}
		cout << endl;



		cout << "v_int: ";
		TemplateVector<int> v_int = { 1, 2, 3, 4 };

		for (size_t i = 0; i < v_int.getSize(); i++)
		{
			cout << v_int[i] << ", ";
		}
		cout << endl;

		cout << "v_double: ";
		TemplateVector<double> v_d = { 1, 2.5, 3, 4.5 };

		for (size_t i = 0; i < v_d.getSize(); i++)
		{
			cout << v_d[i] << ", ";
		}
		cout << endl;

		cout << "v_str: ";
		TemplateVector<std::string> v_str = { "Hello" , "World" };

		for (size_t i = 0; i < v_str.getSize(); i++)
		{
			cout << v_str[i] << ", ";
		}
		cout << endl;


		cout << "Vector Sum Test";
		/*TemplateVector<std::string> v_str1 = { "Hello", "World" };
		TemplateVector<std::string> v_str2 = { ":HI", ":ASDF" };*/

		//TemplateVector<int> v_str1 = { 1,2 };
		//TemplateVector<int> v_str2 = { 3,4 };

		////TemplateVector<std::string> v_str3 =
		//	v_str1 + v_str2;
		///*for (size_t i = 0; i < v_str3.getSize(); i++)
		//{
		//	cout << v_str3[i] << ", ";
		//}
		//cout << endl;*/

		cout << "add and move test: ";

		MyVector v_s_1 = { 1, 2, 3 };
		MyVector v_s_2 = { 1, 2, 3 };
		auto v_s_r = v_s_1 + v_s_2;

		for (size_t i = 0; i < v_s_r.getSize(); i++)
		{
			cout << v_s_r[i] << ", ";
		}
		cout << endl;


		cout << "add and move test2: ";

		TemplateVector<std::string> v_str1 = { "Hello", "World" };
		TemplateVector<std::string> v_str2 = { ":HI", ":ASDF" };

		auto v_str3 = v_str1 + v_str2;
		//using iterator
		for (auto& val : v_str3)
		{
			cout << val << ", ";
		}
		cout << endl;
	}


	
	#pragma  region Vector Implementation
	MyVector::MyVector(int s)
	{
		if (s <= 0)
			throw length_error("Vector -> size cannot be less than 1");

		size = s;
		elem = new double[s];

		for (int i = 0; i < s;i++)
		{
			elem[i] = 0;
		}
	}

	MyVector::MyVector(std::initializer_list<double> lst) : size(lst.size()), elem{ new double[lst.size()] }
	{
		//std::copy(list.begin(), list.end(), elem);
		copy(lst.begin(), lst.end(), elem);
	}

	MyVector::MyVector(const MyVector& v)
	{
		size = v.getSize();

		elem = new double[size];

		for (int i = 0; i < size; i++)
			elem[i] = v[i];
	}

	/*Resource Acquisition Is Initialization (RAII) 
		Avoid naked new and delete OPs. If there is an object that needs to be instantiated with new, 
		wrap it with a class [Containers] that will release it in its destructor. To overcome limitation of keeping that class on the stack,
		use shared pointers(once no one is refering to the class, it will automatically be deleted in theory)
	*/
	MyVector::~MyVector()
	{
		delete[] elem;
	}

	double& MyVector::operator[](int i)
	{
		if (i >= size)
			throw out_of_range("Vector::operator []");
		return elem[i];
	}

	const double& MyVector::operator[](int i) const
	{
		if (i<0 || i >= size)
			throw out_of_range("Vector::operator []");
		return elem[i];
	}

	MyVector& MyVector::operator =(const MyVector& v)
	{
		double* p = new double[v.size];
		for (int i = 0; i != v.size; ++i)
			p[i] = v.elem[i];
		delete[] elem; // delete old elements
		elem = p;
		size = v.size;
		return *this;
	}

	double MyVector::getSum()
	{
		if (size == 0)
			return 0;

		double sum = 0;
		for (int i = 0; i < size; i++)
		{
			sum += this->elem[i];
		}

		return sum;
	}

	int MyVector::getSize() const{ return size; }

	MyVector::MyVector(MyVector&& a)
		//:elem{ a.elem }, // "grab the elements" from a
		//size{ a.size}
	{
		elem = a.elem ; // "grab the elements" from a
		size = a.size;
		a.elem = nullptr; // now a has no elements
		a.size = 0;
	}

	MyVector MyVector::operator +(const MyVector& v)
	{
		if (size != v.getSize())
		{
			throw runtime_error("Vectors are not of the same size");
		}

		MyVector  newV(size);

		for (size_t i = 0; i < this->size; i++)
		{
			newV[i] = elem[i] + v[i];
		}

		return newV;
	}
	#pragma endregion

	#pragma  region Template Vector Implementation
	template<typename T>
	TemplateVector<T>::TemplateVector(int s)
	{
		if (s <= 0)
			throw length_error("Vector -> size cannot be less than 1");

		size = s;
		elem = new T[s];

		/*for (int i = 0; i < s; i++)
		{
			elem[i] = 0;
		}*/
	}

	template<typename T>
	TemplateVector<T>::TemplateVector(std::initializer_list<T> lst) : size(lst.size()), elem{ new T[lst.size()] }
	{
		copy(lst.begin(), lst.end(), elem);
	}

	template<typename T>
	TemplateVector<T>::TemplateVector(const TemplateVector<T>& v)
	{
		size = v.getSize();

		elem = new T[size];

		for (int i = 0; i < size; i++)
			elem[i] = v[i];
	}

	template<typename T>
	TemplateVector<T>::~TemplateVector()
	{
		delete[] elem;
	}

	template<typename T>
	T& TemplateVector<T>::operator[](int i)
	{
		if (i >= size)
			throw out_of_range("Vector::operator []");
		return elem[i];
	}

	template<typename T>
	const T& TemplateVector<T>::operator[](int i) const
	{
		if (i >= size)
			throw out_of_range("Vector::operator []");
		return elem[i];
	}

	template<typename T>
	TemplateVector<T>& TemplateVector<T>::operator =(const TemplateVector<T>& v)
	{
		T* p = new T[v.size];
		for (int i = 0; i != v.size; ++i)
			p[i] = v.elem[i];
		delete[] elem; // delete old elements
		elem = p;
		size = v.size;
		return *this;
	}

	template<typename T>
	int TemplateVector<T>::getSize() const{ return size; }

	template<typename T>
	TemplateVector<T>::TemplateVector(TemplateVector<T>&& a)
		:elem{ a.elem }, // "grab the elements" from a
		size{ a.size }
	{
		a.elem = nullptr; // now a has no elements
		a.size = 0;
	}

	template<typename T>
	TemplateVector<T> TemplateVector<T>::operator +(const TemplateVector<T>& v)
	{
		if (size != v.getSize())
		{
			throw runtime_error("Vectors are not of the same size");
		}

		TemplateVector<T> newV(size);

		for (size_t i = 0; i < this->size; i++)
		{
			newV[i] = elem[i] + v[i];
		}

		return newV;
	}

	template<typename T>
	T* TemplateVector<T>::begin()
	{
		return &elem[0];
	}

	template<typename T>
	T* TemplateVector<T>::end()
	{
		return begin() + size;
	}


	#pragma endregion

}