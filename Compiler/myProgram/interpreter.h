#pragma once
#ifndef INTERFACE   
#define INTERFACE

#include <map>
#include <string>
#include <vector>
using namespace std;

typedef map<string, float> tokenTable;
//A variable table recording the names (strings) of variables
//and the current floating point values of these variables

typedef vector<string> interVector;
//An expression vector is a vector of token strings 

class interpreter
{
public:
	static void interpHome(const vector<string> & lines);
	// this is what is called to facilitate the execution of the
	// program. It calls the four private functions.
private:
	static bool display(const vector<string> & vectOfTokens,
		const vector<tokenCategory> & vectOfCategories,
		int lineNumb,
		tokenTable & valueTable);
	// Displays when the first token is this keyword (can also support equations)

	static bool read(const vector<string> & vectOfTokens, 
		const vector<tokenCategory> & vectOfCategories, 
		int lineNumb,
		tokenTable & valueTable);
	// Reads in when the first token is this keyword (does not support equations)

	static bool assignment(const vector<string> & vectOfTokens,
		const vector<tokenCategory> & vectOfCategories,
		int lineNumb,
		tokenTable & valueTable);
	// Sets values to map tokenVector (can also support equations)

};
#endif