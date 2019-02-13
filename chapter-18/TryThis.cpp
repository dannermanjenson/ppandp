#include <iostream>
#include <string>
#include <vector>
#include "TryThis.h"

using std::cout;
using std::endl;
using std::string;
using std::vector;

struct X
{
	int val;

	void out(const string&s, int nv)
	{
		std::cerr << this << "->" << s << ": " << val << "(" << nv << ")\n";
	}

    // default constructor
	X()
	{
		out("X()", 0);
		val = 0;
	}

	X(int v)
	{
		val = v;
		out("X(int)", v);
	}
    
    // copy constructor
	X(const X& x)
	{
		val = x.val;
		out("X(X&) ", x.val);
	}

    //copy assignment
	X& operator = (const X& a)
	{
		out("X::operator=()", a.val);
		val = a.val;
		return *this;
	}

    //destructor
	~X()
	{
		out("~X()", 0);
	}
};

X copy(X a)
{
	cout << "in copy\n";
	return a;
}

// to illustrate the fact that just calling a function with an object as
// the argument will call the copy constructor
void call(X a)
{
	return;
}

X copy2(X a)
{
	X aa = a; 
	return aa;
}

X& ref_to(X& a)
{
	return a;
}

X* make(int i)
{
	cout << "entering make\n";
	X a(i);
	cout << "made object, returning\n";
	return new X(a);
}

struct XX
{
	X a;
	X b;
};

// global variable to understand how it behaves
//X glob(2);

// blocks of code denote related 'lessons' and can be commented out at such
// to examine each one in a less noisy environment
void TryThis1()
{
	X loc{ 4 };
	call(loc);

	//X loc2{ 3 };
	//loc = X{ 5 };
	//loc2 = copy(loc); // copy creates two objects
	//loc2 = copy2(loc);  // copy2 creates THREE additional objects

	//X loc3{ 6 };
	//X& r = ref_to(loc); // this doesn't trigger any additional copies.

	//delete make(7); // calls int and copy constructor
	//delete make(8); // removing delete logically removes a call to destructor

	//vector<X> v(4);

	//XX loc4;

	//X* p = new X{ 9 };
	//delete p;

	//X* pp = new X[5];
	//delete[] pp;
}

class vector2
{
	int sz;
	double* elem;

public:
    vector2(int s)
		:sz{ s }, elem{ new double[s] }
	{
	}

	~vector2()
	{
		delete[] elem;
	}

	//double operator[](int n) { return elem[n]; }
	double& operator[](int n) { return elem[n]; }
};


void TryThis2()
{
	vector2 v(10);
	double x = v[2];
	v[3] = x;
}
