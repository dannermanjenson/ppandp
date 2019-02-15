#include "pch.h"
#include <iostream>
#include <string>
#include <vector>

template<typename T> 
struct S
{

	S() : val_(0) {}

	S(T initVal)
		: val_(initVal)
	{
	}

	~S() { }
    
	S<T>& operator=(const T& newVal)
	{
		val_ = newVal;
		return *this;
	}

    T& get() { return val_; }
	T& get() const { return val_; }

private:
	T val_;
};


void doDrill()
{
	S<int> my_int(10);
	S<double> my_double(3.14);
	S<char> my_char('a');
	S<std::string> my_string("Sup dawg");

    // this is ugly, would like to initialize more cleanly
	std::vector<int> init_vec{ 10,20,30 };
	S<std::vector<int>>  my_vec(init_vec);

	std::cout << my_int.get() << std::endl;
	std::cout << my_double.get() << std::endl;
	std::cout << my_char.get() << std::endl;
	std::cout << my_string.get() << std::endl;

	for (auto i : my_vec.get())
	{
		std::cout << i << ", " << std::endl;
	}

    my_int= 26;
	std::cout << my_int.get() << std::endl;
}