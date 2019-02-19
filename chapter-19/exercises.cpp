#include "pch.h"
#include "exercises.h"
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using std::vector;
using std::cout;
using std::endl;

// function that adds vec1 to vec0 
template <typename T>
void addVectors(std::vector<T>& vec0, const std::vector<T>& vec1)
{
	int min = std::min(vec0.size(), vec1.size());
	for (int i = 0; i < min; i++)
	{
		vec0[i] += vec1[i];
	}

	return;
}

template <typename T>
void printVector(const std::vector<T> vec)
{
	for (auto i : vec)
	{
		std::cout << i << ", ";
	}
	std::cout << std::endl;
}

void exercise1()
{
    // basic int adding
	std::vector<int> vec0{0, 1, 2};
	std::vector<int> vec1{3, 4, 5, 6};
	addVectors(vec0, vec1);
	printVector(vec0);

    // zero length vector
	std::vector<int> vec2{};
	std::vector<int> vec3{};
	addVectors(vec2, vec3);
	printVector(vec2);

    // mismatch with zero vector
	std::vector<int> vec4{1};
	std::vector<int> vec5{};
	addVectors(vec4, vec5);
	printVector(vec4);

    // strings
	std::vector<std::string> vec6{"Ayy", "Lmao"};
	std::vector<std::string> vec7{"Uh", "huh"};
	addVectors(vec6, vec7);
	printVector(vec6);
}

// have to make an assumption about the return type
template <typename T, typename U>
double multiplyVectors(const std::vector<T>& vt, const std::vector<U>& vu)
{
	int min = std::min(vt.size(), vu.size());
	double sum{ 0 };

	for (int i = 0; i < min; i++)
	{
		sum = sum + vt[i] * vu[i];
	}

	return sum;
}

void exercise2()
{
	vector<int> vec0{0, 1, 2};
	vector<int> vec1{3, 4, 5, 6};
    cout << "Sum is " <<  multiplyVectors(vec0, vec1) << endl;

	vector<double> vec2{5, 1.1, 2.3};
	vector<double> vec3{3.14, 4, 5, 6.2};
    cout << "Sum is " <<  multiplyVectors(vec2, vec3) << endl;

    // not exactly what you would expect but logical
	vector<char> vec4{ 'b', 'c' };
	vector<int>  vec5{ 1, 2, 3 };
    cout << "Sum is " <<  multiplyVectors(vec4, vec5) << endl;

    // logically, this doesn't work since there is no * operator defined for strings
	vector<std::string> vec6{ "hello", "adfg1234" };
	vector<double>      vec7{ 3.14, 867.5309 };
    //cout << "Sum is " <<  multiplyVectors(vec6, vec7) << endl;
}

template <typename X, typename Y>
class Pair
{
public:
	Pair(X x, Y y) :
		x_(x), y_(y)
	{
	}

	~Pair() {}

	X& getX()
	{
		return x_;
	}

	Y& getY()
	{
		return y_;
	}

private:
    // because we don't know what the types can be, we do not want to make
    // any assumptions about what a default state should be. Thus, we hide
    // the default constructor to stop people from creating mutilated objects.
	Pair();

	X x_;
	Y y_;
};

template <typename X, typename Y>
std::ostream& operator<<(std::ostream& os, Pair<X,Y>& pair)
{
	return os << "(" << pair.getX() << ", " << pair.getY() << ")";
}

int ascii_char_to_digit(char ascii_char, std::vector<Pair<char,int>>&  pair)
{
	for (auto i : pair)
	{
		if (ascii_char == i.getX())
		{
			return i.getY();
		}
    }
}

void exercise3()
{
	Pair<int, int> my_pair{ 1, 2 };
	Pair<double, int> my_other_pair{ 3.14, 25 };

	cout << my_pair << endl;
	cout << my_other_pair << endl;

	Pair<std::string, int> test_mapping{ "Danner", 1 };
	cout << test_mapping << endl;

	vector<Pair<char, int>> ascii_digit_table{
        {'0', 0x30}, {'1', 0x31}, {'2', 0x32}, {'3', 0x33}, {'4', 0x34}, 
        {'5', 0x35}, {'6', 0x36}, {'7', 0x37}, {'8', 0x38}, {'9', 0x39} };

	cout << std::hex << ascii_char_to_digit('4', ascii_digit_table) << endl;
}

void runExercises()
{
	//exercise1();
	//exercise2();
	exercise3();
}