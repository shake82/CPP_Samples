namespace ArrayPointerTest
{
	void MainTest();
	void CountCharTest();
	void CustomVectorTest();
	void LambdaTest();
	void VariadicTest();

	class MyVector
	{
	public:
		//MyVector(int s) : size(s), elem{ new double[s] }{}
		MyVector(int s);
		MyVector(std::initializer_list<double> list);
		MyVector(const MyVector& v);
		~MyVector();
		double& operator [](int i);
		//seperate overload for contant variable operation
		const double& operator [](int i) const;
		MyVector& operator =(const MyVector& v);
		double getSum();

		//move operator
		MyVector(MyVector&& a); // move constr uctor
		MyVector& operator=(MyVector&& a); // move assignment

		//const here means that it can be accessable if the MyVector variable is a constant
		int getSize() const;

		//Returning reference caused the receving variable's constructor to be called
		//If a copy is returned, then the move assignment seems to take over
		MyVector operator +(const MyVector& v);
	private:
		int size;	//size of the vectors
		double * elem; // pointer to the first element
	};

	class BaseContainer
	{
	public:
		virtual double& operator [](int i) = 0;
		virtual double getSum() = 0;
		virtual int getSize() = 0;

		//base class destructor is important to make sure that the child class destructor gets called
		//if cast as Base class
		virtual ~BaseContainer(){}
	};

	class Vector_Container: public BaseContainer
	{
	public:
		Vector_Container(int s) : v(s){}
		Vector_Container(std::initializer_list<double> list) : v(list){}
		~Vector_Container(){}
		
		double& operator [](int i) { return v[i]; };
		double getSum() { return v.getSum(); };
		int getSize() { return v.getSize(); };
	private:
		MyVector v;

	};


	template<typename T>
	class TemplateVector
	{
	public:
		TemplateVector(int s);
		TemplateVector(const TemplateVector<T>& v);
		TemplateVector(std::initializer_list<T> list);
		~TemplateVector();

		T& operator[](int i);
		const T& operator[](int i) const;
		TemplateVector<T>& operator =(const TemplateVector<T>& v);

		TemplateVector<T> operator +(const TemplateVector<T>& v);

		//move operator
		TemplateVector(TemplateVector<T>&& a); // move constr uctor
		TemplateVector<T>& operator=(TemplateVector<T>&& a); // move assignment

		//const here means that it can be accessable if the variable is a constant
		int getSize() const;
	
		//itertor methods
		T* begin();
		T* end();
	private:
		T* elem;
		int size;
	};

}