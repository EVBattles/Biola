// Time Worked
// 11/27 3:00 PM - 4:30 PM; 6:30 PM - 11:30 PM 
// 11/28 11:50 AM - 1:15 PM; 6:15 PM - 10:50 PM 

#include <iostream>
#include "lexScanner.h" // allows access to the lexScanner function
#include "expEvaluator.h" // allows acces to the expEvaluator function
#include "interpreter.h" // allows acces to the interpreter function
#include <string>
#include <vector>
#include <map>
#include <iterator>

using namespace std;

bool interpreter::display(const vector<string> & vectOfTokens,
	const vector<tokenCategory> & vectOfCategories,
	int lineNumb,
	tokenTable & valueTable)
// *analyze syntax 
	// *(1) display keyword
	// *(2) " " or variable or expression
	// *...
	// *(n) ; 
	// *print out syntax error message if incorrect (aka, no ;)
// *if " ", print out
// *if variable only, check for it in map tokenTable
	// *if in map tokenTable, print out
	// *if not in map tokenTable, print out runtime error message
// *if variable with equation
	// *send to expEvaluator
		// *true - set variable equal to expValue
		// *false - print out runtime error message
// *return
{
	// Check syntax 
	if (vectOfTokens[vectOfTokens.size() - 1] == ";")
	{
		// this is a good syntax -> continue on with program
		//cout << "Good Syntax \n";
	}
	else
	{
		cout << "Syntax error line " << lineNumb << endl;
		return false;
	}

	//cout << "entering for loop \n";
	for (size_t y = 1; y < vectOfTokens.size(); y++)
	{
		//for (int w = 0; w < vectOfTokens.size(); w++)
		//{
		//	cout << vectOfTokens[w];
		//}
		//cout << endl;
		if (vectOfCategories[y] == STRING_LITERAL)
		{
			cout << vectOfTokens[y].substr(1, vectOfTokens[y].length() - 2) << " ";
			if (vectOfTokens[y + 1] == ",")
			{
				y++;
			}
			else if (vectOfTokens[y + 1] == ";")
			{
				cout << endl;
				return true;
			}
			else
			{
				cout << "Syntax error line " << lineNumb << endl;
				return false;
			}
		}
		else if ((vectOfCategories[y] == ID_NAME) || (vectOfCategories[y] == NUMERICAL_LITERAL))
		{
			if (vectOfCategories[y + 1] == NUMERICAL_OP)
			{
				vector<string> equation;
				for (size_t r = y; r < vectOfTokens.size(); r++)
				{
					if (vectOfTokens[r] == "," || vectOfTokens[r] == ";")
					{
						r = vectOfTokens.size();
					}
					else
					{
						equation.push_back(vectOfTokens[r]);
					}
				}
				//for (int e = 0; e < equation.size(); e++)
				//{
					//cout  << equation[e] << " ";
				//}
				//cout << endl;
				float expValue;
				expVector postfixExp;
				//send to expEvaluator and set result equal to valueTable
				ExpressionEvaluator::infixToPostfixConversion(equation, postfixExp);
				//cout << "Tokens of this postfix expression:" << endl;
				//for (expVector::iterator pos = postfixExp.begin(); pos != postfixExp.end(); pos++)
					//cout << '\t' << *pos << endl;

				if (ExpressionEvaluator::postfixEvaluator(postfixExp, valueTable, expValue))
				{
					//cout << "The value of this expression is " << expValue << endl;
					cout << expValue << " ";
					if (vectOfTokens[y + equation.size()] == ";")
					{
						return true;
					}
					else
					{
						y += equation.size();
					}
				}
				else
				{
					//syntax error
					cout << "Runtime error line " << lineNumb << endl;
					return false;
				}
			}
			else
			{
				cout << valueTable[vectOfTokens[y]] << " ";
			}
		}
		else if (vectOfTokens[y] == ";")
		{
			return true;
		}
		else
		{
			cout << "Syntax error line " << lineNumb << endl;
			return false;
		}
		cout << endl;
	}
}

bool interpreter::read(const vector<string> & vectOfTokens, 
	const vector<tokenCategory> & vectOfCategories, 
	int lineNumb,
	tokenTable & valueTable)

// *analyze syntax
	// *(1) read keyword
	// *(2) value
	// *(3) ;
	// *print out syntax error message if incorrect 
// *check if variable is in map tokenTable
	// *if it is, continue on (replace value in place of current variable)
	// *if it is not, create new variable in map tokenTable
// *print out prompt for value entry
// *create place for entry -> map::operator[]
// *save entry to map tokenTable
// *return
{
	float holder;
	// Check syntax
	if (vectOfCategories[1] == ID_NAME)
	{
		if (vectOfTokens[2] == ";")
		{
			// this is a good syntax -> continue on with program
		}
		else
		{
			// this is a syntax error (print out syntax error with line number
			// quit execution of program
			cout << "Syntax error line " << lineNumb << endl;
			return false;
		}
	}
	else
	{
		// this is a syntax error (print out syntax error with line number
		// quit execution of program
		cout << "Syntax error line " << lineNumb << endl;
		return false;
	}

	//print out prompt for value entry
	//create place for entry if entry is not already there
	//save entry to map tokenTable
	cout << "Please enter " << vectOfTokens[1] << endl;
	cin >> holder;
	valueTable[vectOfTokens[1]] = holder;
	//cout << vectOfTokens[1] << " = " << valueTable[vectOfTokens[1]] << endl;
	return true;
}

bool interpreter::assignment(const vector<string> & vectOfTokens,
	const vector<tokenCategory> & vectOfCategories,
	int lineNumb,
	tokenTable & valueTable)
// *analyze syntax
	// *(1) variable
	// *(2) =
	// *...
	// *(n) ;
	// *print out syntax error message if incorrect
// *test to see if left variable is in the map tokenTable
	// *if it is send right of = to expEvaluator
		// *if true, set left variable = to expValue
		// *if false, print out runtime error message
	// *if it is false, print out runtime error message
// *return
{
	float expValue;
	map <string, float> ::iterator it;
	// check syntax
	//for (int r = 0; r < vectOfTokens.size(); r++)
	//{
		//cout << vectOfTokens[r];
	//}
	//cout << endl;
	if (vectOfTokens[1] == "=")
	{
		//cout << "= is good \n";
		if (vectOfTokens[vectOfTokens.size() - 1] == ";")
		{
			//cout << "; is good \n";
			// this is good syntax -> continue on with program
		}
		else
		{
			//syntax error
			cout << "Syntax error line " << lineNumb << endl;
			return false;
		}
	}
	else
	{
		//syntax error
		cout << "Syntax error line " << lineNumb << endl;
		return false;
	}

	vector<string> infix;

	for (int y = 2; y < vectOfTokens.size() - 1; y++)
	{
		infix.push_back(vectOfTokens[y]);
	}

	expVector postfixExp;
	//send to expEvaluator and set result equal to valueTable
	ExpressionEvaluator::infixToPostfixConversion(infix, postfixExp);
	//cout << "Tokens of this postfix expression:" << endl;
	//for (expVector::iterator pos = postfixExp.begin(); pos != postfixExp.end(); pos++)
		//cout << '\t' << *pos << endl;

	if (ExpressionEvaluator::postfixEvaluator(postfixExp, valueTable, expValue))
	{
		//cout << "The value of this expression is " << expValue << endl;
		valueTable[vectOfTokens[0]] = expValue;
		if (vectOfTokens[vectOfTokens.size() - 1] == ";")
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		ExpressionEvaluator::postfixEvaluator(postfixExp, valueTable, expValue);
		//syntax error
		cout << "Runtime error line " << lineNumb << endl;
		return false;
	}
	
}

void interpreter:: interpHome(const vector<string> & lines)
// *takes in loaded file
// *call lexScanner with file to produce tokens
// *analyze tokens (use loop) for if first token in line is 
	// display
	// read
	// assignment
// and call those methods (do this for every token and vector of tokens)
// *return
{
	vectOfTokenVects myVectOfTokenVects; // NOTE: vector of token vectors (vectors of tokens), so ->
	// a vector of vectors of tokens
	vectOfCategoryVects myVectOfCategoryVects;
	tokenTable valueTable;
	// call lexScanner with file to produce tokens
	//cout << "Calling Lexical Scanner \n";
	LexicalScanner::getLexicalInfo(
		lines,
		myVectOfTokenVects,
		myVectOfCategoryVects);

	//cout << "Display Lexical Information \n";

	//Display the lexical information 
	//LexicalScanner::displayLexicalInfo(
		//myVectOfTokenVects,
		//myVectOfCategoryVects);

	//cout << endl;

	//cout << "Entering Check Loop \n";
	// Loop through every tokenVector
	for (size_t i = 0; i < myVectOfTokenVects.size(); i++)
	{
		// if first tokenVector is display
		if (myVectOfTokenVects[i][0] == "display")
		{
			// call display function
			//cout << "display \n";
			if (!interpreter::display(myVectOfTokenVects[i], myVectOfCategoryVects[i], i + 1, valueTable))
				return;

		}
		// if first token is read
		else if (myVectOfTokenVects[i][0] == "read")
		{
			// call read function
			//cout << "read \n";
			if (!interpreter::read(myVectOfTokenVects[i], myVectOfCategoryVects[i], i + 1, valueTable))
				return;


		}
		// if first token is a ID Name
		else if (myVectOfCategoryVects[i][0] == ID_NAME)
		{
			// call assignment function
			//cout << "assignment \n";
			if (!interpreter::assignment(myVectOfTokenVects[i], myVectOfCategoryVects[i], i + 1, valueTable))
				return;

		}
		// for all other cases (which is really only numbers and symbols 
		// and other keywords at this point)
		else
		{
			// this is an error
			// if it is another keyword, print out "pardon the dust" - not
			//    finished yet
			if (myVectOfCategoryVects[i][0] == KEYWORD)
			{
				cout << "Pardon the dust. The function " << myVectOfCategoryVects[i][0] << "\n in line " << i + 1
					<< " is not yet available. Please try again later. \n";
			}
			else
			{
				cout << "Syntax error, line " << i + 1 << endl;
			}
			return;
		}
	}
}
