
/*
calculator08buggy.cpp

Helpful comments removed.

We have inserted 3 bugs that the compiler will catch and 3 that it won't.
*/

#include "std_lib_facilities.h"
//------------------------------------------------------------------------------
// Token
//------------------------------------------------------------------------------
// definitions for all of the kinds of tokens we can deal with 
const char let = 'L';
const char quit = 'Q';
const char print = ';';
const char number = '8';
const char name = 'a';
const char square_root = 's';
const char power = 'p';

// struct to hold a basic unit of an expression.
// This can be numbers, symbols or variables
struct Token {
	char kind;
	double value;
	string name;
	Token(char ch) :kind(ch), value(0) { }
	Token(char ch, double val) :kind(ch), value(val) { }
	Token(char ch, string s) :kind(ch), name(s){}
};

//------------------------------------------------------------------------------
// Token stream
//------------------------------------------------------------------------------
// class implementing a token stream. Acts as a buffer between cin and where
// processing happens
class Token_stream {
	bool full;
	Token buffer;
public:
	Token_stream() :full(0), buffer(0) { }

	Token get();
	void unget(Token t) { buffer = t; full = true; }

	void ignore(char);
};

// method to get a token from the token stream
Token Token_stream::get()
{
	if (full) { full = false; return buffer; }
	char ch;
	cin >> ch;
	switch (ch) {
	case '(': case ')': case '+': case '-':
	case '*': case '/': case '%': case ';':
	case '=': case ',':
		return Token(ch);
	case '.': case '0': case '1': case '2':
	case '3': case '4': case '5': case '6':
	case '7': case '8': case '9':
	{	
		cin.unget();
	    double val;
	    cin >> val;
	    return Token(number, val);
	}
	default:
		if (isalpha(ch)) 
		{
			string s;
			s += ch;
			while (cin.get(ch) && (isalpha(ch) || isdigit(ch)))
			{
				s += ch;
			}
			cin.unget();
			if (s == "let")  return Token(let);
			if (s == "quit") return Token(name);
			if (s == "sqrt") return Token(square_root);
			if (s == "pow")  return Token(power);
			return Token(name, s);
		}
		error("Bad token");
	}
}

// method to ignore characters in the token stream
void Token_stream::ignore(char c)
{
	if (full && c == buffer.kind) {
		full = false;
		return;
	}
	full = false;

	char ch;
	while (cin >> ch)
		if (ch == c) return;
}

//------------------------------------------------------------------------------
// Variable 
//------------------------------------------------------------------------------
// struct to hold information about a variable
// stores a name, value pair
struct Variable {
	string name;
	double value;
	Variable(string n, double v) :name(n), value(v) { }
};

// global vector to hold all variables for the life of the program
vector<Variable> names;

// function to retrieve a variable value from names
double get_value(string s)
{
    for (Variable x : names)
    {
        if (x.name == s) return x.value;
    }
	error("get: undefined name ", s);
}

// function to set a value of a variable alread in names
void set_value(string s, double d)
{
	for (Variable x : names)
	{
		if (x.name == s) 
		{
			x.value = d;
			return;
		}
	}
	error("set: undefined name ", s);
}

// function to see if a variable is already declared in names
bool is_declared(string s)
{
	for (Variable x : names)
	{
		if (x.name == s) return true;
	}
	return false;
}

// function to add variables programatically
bool define_name(string s, double val)
{
	if (is_declared(s))
	{
		return false;
	}
	names.push_back(Variable(s, val));
}

// global token stream buffer for use during the life of the program
Token_stream ts;

//------------------------------------------------------------------------------
// Grammar 
//------------------------------------------------------------------------------
// declaration of expression so primary() can use it
double expression();

// function to retrieve a primary from ts 
double primary()
{
	Token t = ts.get();
	switch (t.kind) {
	case '(':             // this case has been modified by pow and does not work
	{	
		double d = expression();
	    t = ts.get();
		if (t.kind == ')')
		{
			return d;
		}
		else if (t.kind == ',')
		{
			return d;
		}
		else
		{
			error("'(' expected");
		}
	}
	case square_root:
	{
		double d = expression();
		if (d < 0) error("attempted square of negative number");
		return sqrt(d);
	}
	case '-':
		return -primary();
	case '+':
		return primary();
	case power:
	{
		return pow(expression(), expression()); // this does not work correctly
	}
	case number:
		return t.value;
	case name:
		return get_value(t.name);
	default:
		error("primary expected");
	}
}

// function to retieve a term from ts
double term()
{
	double left = primary();
	while (true) {
		Token t = ts.get();
		switch (t.kind) {
		case '*':
			left *= primary();
			break;
		case '/':
		{	
			double d = primary();
		    if (d == 0) error("divide by zero");
		    left /= d;
		    break;
		}
		case '%':
		{
			int i1 = narrow_cast<int>(left);
			int i2 = narrow_cast<int>(primary());
			if (i2 == 0) error("%: divide by zero");
			left = i1 % i2;
			break;
		}
		default:
			ts.unget(t);
			return left;
		}
	}
}

// function to retrieve an expression from ts
double expression()
{
	double left = term();
	while (true) {
		Token t = ts.get();
		switch (t.kind) {
		case '+':
			left += term();
			break;
		case '-':
			left -= term();
			break;
		default:
			ts.unget(t);
			return left;
		}
	}
}

// function to retrieve a declaration from ts
double declaration()
{
	Token t = ts.get();
	if (t.kind != name) error("name expected in declaration");
	string name = t.name;
	if (is_declared(name)) error(name, " declared twice");
	Token t2 = ts.get();
	if (t2.kind != '=') error("= missing in declaration of ", name);
	double d = expression();
	names.push_back(Variable(name, d));
	return d;
}

// function to retrieve a statement from ts
double statement()
{
	Token t = ts.get();
	switch (t.kind) {
	case let:
		return declaration();
	default:
		ts.unget(t);
		return expression();
	}
}

// function to clean up ts, cleaning up input so we can recover from errors
void clean_up_mess()
{
	ts.ignore(print);
}

const string prompt = "> ";
const string result = "= ";
const int    precision = 10;

// top level grammar for Calculation 
void calculate()
{
	define_name("k", 1000);

	while (true)
	{
		try 
		{
			cout << prompt;
			Token t = ts.get();
			while (t.kind == print) 
			{ 
				t = ts.get(); 
			}
			if (t.kind == quit)
			{
				return;
			}
			ts.unget(t);
			cout << setprecision(precision) << result << statement() << endl;
		}
		catch (runtime_error& e) {
			cerr << e.what() << endl;
			clean_up_mess();
		}
	}
}

//------------------------------------------------------------------------------
// Entry point 
//------------------------------------------------------------------------------
int main()
{
	try 
	{
		calculate();
		return 0;
	}
	catch (exception& e) 
	{
		cerr << "exception: " << e.what() << endl;
		char c;
		while (cin >> c&& c != ';');
		return 1;
	}
	catch (...) 
	{
		cerr << "exception\n";
		char c;
		while (cin >> c && c != ';');
		return 2;
	}
}