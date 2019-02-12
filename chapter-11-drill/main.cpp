#include "std_lib_facilities.h"

int main()
{
	double val = 1234567.89;

	cout << "default: " << defaultfloat << val << '\n';
	cout << "fixed: " << fixed << val << '\n';
	cout << "scientific: " << scientific << val << '\n';

	return 0;
}