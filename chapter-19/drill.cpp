#include "pch.h"
#include <iostream>
#include <string>
#include <vector>

// struct that emulates a simple version of a vector.
// The purpose is to practice the implementation details of
// a vector in the drill problems.
template<typename T> 
struct S
{
	S() : val_(0) {}

	S(T initVal)
		: val_(initVal)
	{
	}

	~S() { }

	S(const S&)
	{

	}
    
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

// output operator for S struct
template <typename T>
std::ostream& operator<<(std::ostream& os, S<T>& obj)
{
	return os << obj.get();
}

// input operator for S struct
template <typename T>
std::istream& operator>>(std::istream& is, S<T>& obj)
{
	// read obj from stream
	is >> obj.get();

	if ( !is)
		is.setstate(std::ios::failbit);

	return is;
}

// Helper function to simplify the prompting of value reading
// into any arbitrary T.
template <typename T> 
void read_val(T& v, const std::string& type)
{
	std::cout << "Please enter a " << type << std::endl;
	std::cin >> v;
	std::cout << "your " << type << " is " << v << std::endl;
}

// drill exercises from 1-11
void doDrill_1()
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

// drill exercises from 12-14
void doDrill_2()
{
	S<int> my_int(10);
	S<double> my_double(3.14);
	S<char> my_char('a');
	S<std::string> my_string("Sup dawg");
	std::vector<int> init_vec{ 10,20,30 };
	S<std::vector<int>>  my_vec(init_vec);

	std::cout << my_int << std::endl;
	std::cout << my_double << std::endl;
	std::cout << my_char << std::endl;
	std::cout << my_string << std::endl;

	read_val<S<int>>(my_int, "int");
	read_val<S<double>>(my_double, "double");
	read_val<S<char>>(my_char, "char");
	read_val<S<std::string>>(my_string, "string");
    // figure out this bonus after doing some exercises
	//read_val<S<std::vector<int>>(my_vec, "vector");
}

void doDrill()
{
	//doDrill_1();
	//doDrill_2();
}