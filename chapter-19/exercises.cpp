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

// helper function to print the contents of a vector
template <typename T>
void printVector(const std::vector<T> vec)
{
	for (auto i : vec)
	{
		cout << i << ", ";
	}
	cout << endl;
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

// Function that multiplies two vectors member-wise and adds the results.
// have to make an assumption about the return type if we want to
// sum all vector components into a single value
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

// Pair class 
// Practice the use of a templated class with multiple template types.
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

// output stream operator for Pair class
template <typename X, typename Y>
std::ostream& operator<<(std::ostream& os, Pair<X,Y>& pair)
{
	return os << "(" << pair.getX() << ", " << pair.getY() << ")";
}

// function to do map translation between an ascii character to digit
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

// Link class to implement the nodes in a double linked list
// struct is used to make all variables public for better practice.
// It also simplifies the writing of the helper functions because
// I can call the variables directly without having to write an accessor
// for every one.
template <typename T>
struct Link
{
	Link(const T& val)
		: value_(val)
	{
	}

	Link(const T& val, Link* p, Link* n)
	    :value_(val), prev_(p), next_(n)
	{
	}
	~Link() 
	{
	}

	void Identify()
	{
        cout << value_ << ":0x" << std::hex << this << endl;
		cout << "\t" << std::hex << "prev_:0x" << prev_ << endl;
		cout << "\t" << std::hex << "next_:0x" << next_ << endl;
	}

	T value_;
	Link* prev_{ nullptr };
	Link* next_{ nullptr };

private:
    // hiding the default constructor
	Link();
};

// helper function for Link class to print an entire list of nodes
template <typename T>
void printList(Link<T>* head)
{
	while (head != nullptr)
	{
		head->Identify();
		head = head->next_;
	}
}

// Helper function for Link class to insert newLink before node
// returns newLink if newLink is not nullptr, else returns node
template <typename T>
Link<T>* insert(Link<T>* node, Link<T>* newLink)
{
	if (node == nullptr) return newLink;
	if (newLink == nullptr) return node;

	newLink->next_ = node;
	if (node->prev_ != nullptr)
	{
		node->prev_->next_ = newLink;
	}
	newLink->prev_ = node->prev_;
	node->prev_ = newLink;
	return newLink;
}

// tests for insert helper function
void insertTests()
{
	cout << "--- Running Link:insert tests ---" << endl;
	cout << "Output should be Brian, Thor, Josh, Odin" << endl;

    // Odin
	Link<std::string>* norse_gods = new Link<std::string>( "Odin", nullptr, nullptr );

    // inserting one link by hand
    // Thor Odin
	norse_gods = new Link<std::string>("Thor",nullptr, norse_gods);
	norse_gods->next_->prev_ = norse_gods;

    // inserting link at the end of the list by hand 
    // Thor Josh Odin
	insert(norse_gods->next_, new Link<std::string>("Josh"));

    // inserting Brian at the beginning
    // Brian Thor Josh Odin
	norse_gods =insert(norse_gods, new Link<std::string>("Brian"));
	printList(norse_gods);
}

// helper function for adding a newLink after node
// returns newLink
template <typename T>
Link<T>* add(Link<T>* node, Link<T>* newLink)
{
	if (node == nullptr) return newLink;
	if (newLink == nullptr) return node;

	newLink->prev_ = node;

	if (node->next_ != nullptr)
	{
		node->next_->prev_ = newLink;
	}
	newLink->next_ = node->next_;
	node->next_ = newLink;
	return newLink;
}

// tests for add helper function
void addTests()
{
	cout << "--- Running Link:add tests ---" << endl;
	cout << "Output should be Odin, Josh, Thor" << endl;

    // Odin
	Link<std::string>* norse_gods = new Link<std::string>( "Odin", nullptr, nullptr );
    
    // Adding Thor
    // Odin Thor
	add(norse_gods, new Link<std::string>("Thor"));

    // Adding josh
    // Odin Josh Thor
	add(norse_gods, new Link<std::string>("Josh"));
	printList(norse_gods);
}

// helper function to erase nodes from the list
// returns link before the one erased
template <typename T>
Link<T>* erase(Link<T>* node)
{
	if (node == nullptr) return nullptr;


}

// helper functions to free all memory associated with a list
template <typename T>
bool freeLinks(Link<T*> head)
{
}

void listOpsTests()
{
	//insertTests();
	addTests();
}

// Class describing the stats of a god
class God
{
public:
	God(std::string name,    std::string mythology,
		std::string vehicle, std::string weapon)
	    : name_(name),       mythology_(mythology),
          vehicle_(vehicle), weapon_(weapon)
	{}

	std::string& getName() { return name_; };
	std::string& getMythology() { return mythology_; };
	std::string& getVehicle() { return vehicle_; };
	std::string& getWeapon() { return weapon_; };

private:
	std::string name_{ "" };
	std::string mythology_{ "" };
	std::string vehicle_{ "" };
	std::string weapon_{ "" };
};

// output stream operator for Pair class
std::ostream& operator<<(std::ostream& os, God god)
{
	return os <<         god.getName() << endl
		      << "\t" << god.getMythology() << endl
		      << "\t" << god.getVehicle() << endl
		      << "\t" << god.getWeapon() << endl;
}

void GodLists()
{
	Link<God>* norse_gods= new Link<God>(God{ "Thor", "Norse", "Mjollnir", "Mjollnir" });
	norse_gods = insert(norse_gods, new Link<God>(God{ "Odin", "Norse", "Sleipner", "Gungnir" }));
	printList(norse_gods);
}

void exercise4()
{
	GodLists();
}

void runExercises()
{
	//exercise1();
	//exercise2();
	//exercise3();
	//exercise4();
	listOpsTests();
}