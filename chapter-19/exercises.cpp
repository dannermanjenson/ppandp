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

void runExercises()
{
	//exercise1();
	exercise2();
}