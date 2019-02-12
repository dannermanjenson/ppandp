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
			cout << a[i] << ", ";
        }
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
		cout << ints[i] << ", ";
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

	delete[] myInts;
}