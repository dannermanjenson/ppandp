#include <iostream>
#include <vector>

#include "drill.h"

using std::cout;
using std::endl;
using std::vector;

int ga[] = { 1, 2, 4, 8, 16, 32, 64, 128, 256, 512 };

void printArray(int* array, int size)
{
	cout << "Printing array" << endl;
	for (int i = 0; i < size; i++)
	{
		cout << array[i] << ", ";
	}
	cout << endl;
}

void f(int* array, int size)
{
	int la[10] = { 0 };
	int* p = new int[10]; //messed this up with () instead of [], caused exceptions
   
	for (int i = 0; i < size; i++) 
	{ 
		la[i] = array[i];
		p[i] = array[i];
	};
    
	printArray(la, 10);
	printArray(p, 10);

	delete[] p;
}

void ArrayDrill()
{
	f(ga, 10);
	int aa[] = { 1, 
                 2,
                 3 * 2,
                 4 * 3 * 2,
                 5 * 4 * 3 * 2, 
		         6 * 5 * 4 * 3 * 2,
		         7 * 6 * 5 * 4 * 3 * 2,
		         8 * 7 * 6 * 5 * 4 * 3 * 2,
		         9 * 8 * 7 * 6 * 5 * 4 * 3 * 2,
	             10* 9 * 8 * 7 * 6 * 5 * 4 * 3 * 2};

	f(aa, 10);
}

vector<int> gv{ 1, 2, 4, 8, 16, 32, 64, 128, 256, 512 };

void printVec(vector<int> v)
{
	cout << "Printing vector" << endl;
	for (auto i : v)
	{
		cout << i << ", ";
	}
	cout << endl;
}

void otherF(vector<int> v)
{
	vector<int> lv(v.size());

	lv = v;

	printVec(lv);

	vector<int> lv2(lv);

	printVec(lv2);

}

void VectorDrill()
{
	otherF(gv);

	vector<int> vv { 1, 
                 2,
                 3 * 2,
                 4 * 3 * 2,
                 5 * 4 * 3 * 2, 
		         6 * 5 * 4 * 3 * 2,
		         7 * 6 * 5 * 4 * 3 * 2,
		         8 * 7 * 6 * 5 * 4 * 3 * 2,
		         9 * 8 * 7 * 6 * 5 * 4 * 3 * 2,
	             10* 9 * 8 * 7 * 6 * 5 * 4 * 3 * 2};
	otherF(vv);
}

void DoDrill()
{
	ArrayDrill();
	VectorDrill();
}