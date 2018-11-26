
//
// This is example code from Chapter 6.7 "Trying the second version" of
// "Software - Principles and Practice using C++" by Bjarne Stroustrup
//

/*
This file is known as calculator02buggy.cpp

I have inserted 5 errors that should cause this not to compile
I have inserted 3 logic errors that should cause the program to give wrong results

First try to find an remove the bugs without looking in the book.
If that gets tedious, compare the code to that in the book (or posted source code)

Happy hunting!

*/

#include "std_lib_facilities.h"

constexpr char QUIT_CHAR  = 'x';
constexpr char PRINT_CHAR = '=';

//------------------------------------------------------------------------------

class Token
{
public:
	char kind;        // what kind of token
	double value;     // for numbers: a value 
	Token(char ch)    // make a Token from a char
		:kind(ch), value(0) { }
	Token(char ch, double val)     // make a Token from a char and a double
		:kind(ch), value(val) { }
};

//------------------------------------------------------------------------------

class Token_stream 
{
public:
	Token_stream();   // make a Token_stream that reads from cin
	Token get();      // get a Token (get() is defined elsewhere)
	void putback(Token t);    // put a Token back
private:
	bool full;        // is there a Token in the buffer?
	Token buffer;     // here is where we keep a Token put back using putback()
};

//------------------------------------------------------------------------------

// The constructor just sets full to indicate that the buffer is empty:
Token_stream::Token_stream()
	:full(false), buffer(0)    // no Token in buffer
{
}

//------------------------------------------------------------------------------

// The putback() member function puts its argument back into the Token_stream's buffer:
void Token_stream::putback(Token t)
{
	if (full == true) error("putback() into a full buffer");
	buffer = t;       // copy t to buffer
	full = true;      // buffer is now full
}

//------------------------------------------------------------------------------

// method grabs a token from either the stream or cin and returns it
Token Token_stream::get()
{
	if (full == true)        // do we already have a Token ready?
	{				         // remove token from buffer
		full = false;
		return buffer;
	}

	char ch = '\0';
	cin >> ch;    // note that >> skips whitespace (space, newline, tab, etc.)

	switch (ch) 
	{
	case PRINT_CHAR:    // for "print"
	case QUIT_CHAR :    // for "quit"
	case '(': case ')': case '+': case '-': case '*': case '/':
		return Token(ch);        // let each character represent itself
    
	// this case handles the reading of a floating point number
	case '.':
	case '0': case '1': case '2': case '3': case '4':
	case '5': case '6': case '7': case '9':
	{
		cin.putback(ch);         // put digit back into the input stream
		double val;
		cin >> val;              // read the value as a floating-point number
		return Token('8', val);  // let '8' represent "a number"
	}
	default:
		error("Bad token");
	}
}

//------------------------------------------------------------------------------

Token_stream ts;        // provides get() and putback() 

						//------------------------------------------------------------------------------

double expression();    // declaration so that primary() can call expression()

						//------------------------------------------------------------------------------

						// deal with numbers and parentheses
double primary()
{
	Token t = ts.get();
	switch (t.kind) 
	{
        case '(':    // handle '(' expression ')'
        {
            double d = expression();
            t = ts.get();
            if (t.kind != ')') error("')' expected)");
                return d;
        }
        case '8':            // we use '8' to represent a number
            return t.value;  // return the number's value
        default:
            error("primary expected");
	}
}

//------------------------------------------------------------------------------

// deal with *, /, and %
double term()
{
	double left = primary();
	Token t = ts.get();        // get the next token from token stream

	while (true) 
	{
		switch (t.kind) 
		{
		case '*':
			left *= primary();
			t = ts.get();
			break;
		case '/':
		{
			double d = primary();
			if (d == 0) error("divide by zero");
			left /= d;
			t = ts.get();
			break;
		}
		default:
			ts.putback(t);     // put t back into the token stream
			return left;
		}
	}
}

//------------------------------------------------------------------------------

// deal with + and -
double expression()
{
	double left = term();      // read and evaluate a Term
	Token t = ts.get();        // get the next token from token stream

	while (true) 
	{
		switch (t.kind) 
		{
		case '+':
			left += term();    // evaluate Term and add
			t = ts.get();
			break;
		case '-':
			left += term();    // evaluate Term and subtract
			t = ts.get();
			break;
		default:
			ts.putback(t);     // put t back into the token stream
			return left;       // finally: no more + or -: return the answer
		}
	}
}

//------------------------------------------------------------------------------

int main()
{
	double val = 0.0;

	try
	{
		while (cin) // keep looping so long as cin is getting valid input 
		{
			Token t = ts.get();

			if (t.kind == QUIT_CHAR)        // 'x' for quit
			{
                break;
			}
			if (t.kind == PRINT_CHAR)        // '=' for "print now"
			{
				cout << "=" << val << '\n';
			}
			else
			{
				ts.putback(t);
			}
			val = expression();
		}
		keep_window_open();
	}
	catch (exception& e) {
		cerr << "error: " << e.what() << '\n';
		keep_window_open("~~");
		return 1;
	}
	catch (...) {
		cerr << "Oops: unknown exception!\n";
		keep_window_open("~~");
		return 2;
	}
}
//------------------------------------------------------------------------------
