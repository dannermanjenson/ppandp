#include <iostream>
#include <fstream>
#include <stdexcept>
#include <string>
#include <vector>

using std::cout;
using std::cin;
using std::endl;
using std::ifstream;
using std::string;
using std::vector;

class Point
{
public:
	Point() {}

	Point(int x, int y)
	:x_(x), y_(y){}

	~Point() {}

	int x_{ 0 };
	int y_{ 0 };
};

// output operator for Point type
std::ostream& operator<<(std::ostream& os, const Point& p)
{
	return os << '(' << p.x_ << ',' << p.y_ << ')';
}

// input operator for Point type
std::istream& operator>>(std::istream& is, Point& p)
{
	int x{ 0 };
	int y{ 0 };
	char c0{ '\0' };
	char c1{ '\0' };
	char c2{ '\0' };

	is >> c0 >> x >> c1 >> y >> c2;

	if (!is) return is; // something bad happened 

	if (c0 != '(' || c1 != ',' || c2 != ')') // check formatting
	{
		is.clear(std::ios_base::failbit);
		return is;
	}

	p = Point{ x, y };
	return is;
}

enum args
{
    PROG_NAME = 0,
    IN_FILE_NAME,
    NUM_ARGS,
};

// prints contents of the points vector
void printPoints(vector<Point>& points)
{
	for (Point x : points)
		cout << x << '\n';
}

// takes an input stream and attempts to read points from it
// places them into vector points
void processInputPoints(ifstream& ist, vector<Point>& points)
{
    for (Point p; ist >> p; ) // read all points from the file
    {
        points.push_back(p);
    }
}

int main(int argc, char** argv)
{
	if (argc != args::NUM_ARGS)
	{
		cout << "Error, no input file. Please specify one." << endl;
		return 1;
	}
	try
	{
		std::ifstream ist{ argv[args::IN_FILE_NAME] };

		if (!ist) throw string("file name not found\n");
    
		vector<Point> original_points;

		processInputPoints(ist, original_points);

		printPoints(original_points);

	}
	catch (string e)
	{
		cout << "Error, " << e << endl;
	}
	catch (...)
	{
		std::cerr << "exception\n";
		char c;
		while (cin >> c && c != ';');
		return 2;
	}

	return 0;
}