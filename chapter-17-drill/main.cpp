#include <iostream>
#include <vector>

using std::cout;
using std::endl;
using std::ostream;
using std::vector;

void print_array10(ostream& os, int* a, int numInts)
{
	if (a)
	{
        for (int i = 0; i < numInts; i++)
        {
			os << a[i] << ", ";
        }
		os << endl;
	}
}

void allocateIntegers(int** a, int numInts)
{
	*a = new int[numInts];

	for (int i = 0; i < numInts; i++)
	{
		(*a)[i] = 100 + i; // using parens to specify dereference order
	}
}

void initVector(vector<int>& ints)
{
	for (int i = 0; i < ints.size(); i++)
	{
		ints[i] = 100 + i;
	}
}

void prINTVector(ostream& os, vector<int>& ints)
{
	for (int i = 0; i < ints.size(); i++)
	{
		os << ints[i] << ", ";
	}
	os << endl;
}

void pointerFun()
{
	int myInt = 7;
	int* p1 = &myInt;
	cout << "Pointer:" << p1 << " Value:" << *p1 << endl;

	int* p2 = new int[7];

	for (int i = 0; i < 7; i++)
	{
		p2[i] = 2 * i;
	}

	cout << "Pointer:" << p2 << endl;
	print_array10(cout, p2, 7);
	cout << endl;

	int* p3 = p2;
	p2 = p1;
	p2 = p3;

	cout << "Pointer:" << p1 << " Value:" << *p1 << endl;
	cout << "Pointer:" << p2 << " Value:" << *p2 << endl;

	delete[] p2;
}

void arrayCopyExample()
{
	cout << "Array copy example:" << endl;
	int* p1 = new int[10];
	int* p2 = new int[10];
   
	for (int i = 0; i < 10; i++)
	{
		p1[i] = i * 2;
		p2[i] = 0;
	}

	print_array10(cout, p1, 10);
	print_array10(cout, p2, 10);

	for (int i = 0; i < 10; i++)
	{
		p2[i] = p1[i];
	}

	print_array10(cout, p1, 10);
	print_array10(cout, p2, 10);

	delete[] p1;
	delete[] p2;
}

void vectorCopyExample()
{
	cout << "Vector copy example" << endl;

	vector<int> p1(10);
	vector<int> p2(10);

	if (p1.size() == p2.size())
	{
        for (int i = 0; i < p1.size(); i++)
        {
			p1[i] = 2 * i;
			p2[i] = 0;
        }
        
		prINTVector(cout, p1);
		prINTVector(cout, p2);

		p2 = p1;

		prINTVector(cout, p1);
		prINTVector(cout, p2);
	}
	else
	{
		cout << "error, p1 is not the same size as p2" << endl;
	}
}

int main()
{
	cout << "Array version:" << endl;
	int* myInts = nullptr;
	allocateIntegers(&myInts, 20);
	print_array10(cout, myInts, 20);

	cout << "\n\n";

	cout << "Vector version:" << endl;
	vector<int> myOtherInts(20);
	initVector(myOtherInts);
	prINTVector(cout, myOtherInts);

	cout << "\n\n";

	pointerFun();

	arrayCopyExample();
	vectorCopyExample();

	delete[] myInts;
}