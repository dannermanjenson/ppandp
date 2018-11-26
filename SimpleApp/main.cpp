#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

enum Units
{
    IN = 0,
    CM = 1,
    M  = 2,
    FT = 3,
};

// precalculating the factors for conversions to meters
constexpr double CM2M_FACTOR = 100.0;
constexpr double IN2M_FACTOR = 2.54 * 1 / CM2M_FACTOR;
constexpr double FT2M_FACTOR = 12.0 * IN2M_FACTOR;

/*
This is used by accessing unit_conversion_matrix in the same order you wish to
do the conversion.

ex)                                                
I want to convert value from CM to M
   value_in_cm = value * unit_conversion_matrix[CM][M]

Factors are compensated such that you always multiply the value by the factor
to perform the conversion
*/

double unit_conversion_matrix[4][4]
{
//       IN        CM          M           FT
/*IN*/   {1,       1.0/2.54,   0.0254,     12},
/*CM*/   {2.54,    1,          1.0/100.0,  0.0328084},
/*M*/    {39.3701, 100,        1,          3.28084},
/*FT*/   {1.0/12.0,30.48,      0.3048,     1}
};


double convertToMeters(std::string inUnit, double value)
{
	if (inUnit == "cm")
	{
		return value * unit_conversion_matrix[CM][M];
    }

	if (inUnit == "m")
	{
		return value * unit_conversion_matrix[M][M];
	}

	if (inUnit == "in")
	{
		return value * unit_conversion_matrix[IN][M];
	}

	if (inUnit == "ft")
	{
		return value * unit_conversion_matrix[FT][M];
	}

	return 0;
}

bool isValidUnit(std::vector<std::string> validUnits, std::string unitToCheck)
{
		bool inList = false;             // must initialize the flag to false
		for (std::string x : validUnits)
		{
			if (x == unitToCheck)        // search the list for valid units
			{
				inList = true;
			}
		}

		return inList;
}

int main()
{
	double x = 0;
	double y = 0;

	double smallest = 0;
	double largest = 0;
	double temp = 0;
	double total = 0;

	bool firstRun = true;
	int numEntries = 0;

	std::string temp_unit{ "" };
	std::vector<std::string> units{"cm", "m", "in", "ft"};
	std::vector<double> values{ };

	while (std::cin >> temp >> temp_unit)
	{
		if (true == isValidUnit(units, temp_unit))
		{
			std::cout << "Got " << temp << temp_unit << '\n';
			temp = convertToMeters(temp_unit, temp); // convert for uniform 
                                                     // comparison
			values.push_back(temp);

			total = total + temp; 
			numEntries++;

			if (firstRun == true) // handling the base case of the while loop 
			{                     // where the first entry is both the largest
				smallest = temp;  // and the smallest thus far
				largest = temp;
				firstRun = false;
			}

			if (temp < smallest)
			{
				smallest = temp;
				std::cout << "smallest thus far" << '\n';
			}

			if (temp > largest)
			{
				largest = temp;
				std::cout << "largest thus far" << '\n';
			}

			std::cout << "running total is " << total << '\n';
		}
		else
		{
			std::cout << "invalid units\n";
		}
	}

	std::sort(values.begin(), values.end());

	std::cout << "Smallest: " << smallest << '\n';
	std::cout << "Largest: " << largest << '\n';
	std::cout << "Total: " << total << '\n';
	std::cout << "List of values : " << '\n';
	std::cout << "-----------------" << '\n';
	for (double x : values)
	{
		std::cout << x << "m\n";
	}
}