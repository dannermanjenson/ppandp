#include <iostream>
#include <fstream>
#include <stdexcept>
#include <string>
#include <vector>

using std::cout;
using std::cin;
using std::endl;
using std::ifstream;
using std::ofstream;
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

// equality operator for Point Type
bool operator==(const Point& a, const Point& b)
{
	if ((a.x_ == b.x_) && (a.y_ == b.y_)) return true;

	return false;
}

// inequality operator for Point Type
bool operator!=(const Point& a, const Point& b)
{
	if ((a.x_ != b.x_) || (a.y_ != b.y_)) return true;

	return false;
}

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

// defines enumeration for arguments we are expecting on the command line
enum args
{
    PROG_NAME = 0,
    IN_FILE_NAME,
    OUT_FILE_NAME,
    NUM_ARGS,
};

// writes a vector of points to an output stream
void outputPoints(ofstream& ost, vector<Point>& points)
{
	for (Point x : points)
		ost << x << '\n';
}

// prints contents of the points vector
void printPoints(vector<Point>& points)
{
	for (Point x : points)
		cout  << '\t' << x << '\n';
}

// takes an input stream and attempts to read points from it
// places them into vector points
void processPoints(ifstream& ist, vector<Point>& points)
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
		ifstream ist{ argv[args::IN_FILE_NAME] };
		ist.exceptions(ist.exceptions() | std::ios_base::badbit);

		if (!ist) throw string("file name not found");
    
		vector<Point> original_points;

		processPoints(ist, original_points);
		ist.close();
		cout << "Original points:" << endl;
		printPoints(original_points);

		ofstream ost{ argv[args::OUT_FILE_NAME] };
		ost.exceptions(ost.exceptions() | std::ios_base::badbit);

		if (!ost) throw string("problem with output file");
        
		outputPoints(ost, original_points);
		ost.close();

		ifstream readBack{ argv[args::OUT_FILE_NAME] }; // read back the output
		readBack.exceptions(readBack.exceptions() | std::ios_base::badbit);

		if (!readBack) throw string("problem reading back the output file");

		vector<Point> processed_points;
		processPoints(readBack, processed_points);
		cout << "Processed points:" << endl;
		printPoints(processed_points);

        // uncomment this to test the failure
		//processed_points.push_back(Point{ -1,-1 });

		if (original_points != processed_points)
			cout << "Something's wrong!\n";
	}
	catch (string e)
	{
		cout << "Error, " << e << '\n' << endl;
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