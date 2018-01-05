
#include <iostream>     //including I/O support
#include <fstream>      //including file I/O support
#include <vector>		//including support of vector container
#include <string>		//including the new C++ string class support
#include <cstring>		//including old C character array support
#include <conio.h>		//including support to use _getch()
						//	to read one char at a time from user input
#include <ostream>

#include "interface.h"	// allows access to the interface header
#include "lexScanner.h" // allows access to the lexical scanner header
#include "expEvaluator.h" // allows access to the expEvaluator header
#include "interpreter.h" // allows acces to the interpreter header

using namespace std;


// 1. Read in a program (lines of statements) from a file
void Interface::loadProgramFromFile()
{
	char fileName[MaxLengthFileName];	
	// this char array stores the name of the file the program reads from.

	cout<<"Name of file to upload program from (ex. file.txt): ";
	cin >> fileName;
	while( strlen(fileName) == 0 )
	{
		cin >> fileName;
	}

	ifstream inFile;
	inFile.open( fileName );
	if ( inFile.fail() )
	{ cout << endl << "Cannot open this file!" << endl;
	return;
	}

	lines.clear();  //Delete all the lines of statements
	string inputBuffer;
	while( !inFile.eof() )
	{
		getline(inFile, inputBuffer);
		while( !inFile.eof() && inputBuffer.size() == 0 )
		{
			getline(inFile, inputBuffer);
		}

		if (!inFile.eof())
		{
  			cout<< "Line["
				<< lines.size()
				<< "] read:"
				<< inputBuffer << endl;
			lines.push_back(inputBuffer);
		}

	}

	inFile.close();
}



// 2. Display the lines of statements
void Interface::displayProgram()
{
	for (int i = 0; i < lines.size(); i++) // loop to call every string in the vector
	{
		cout << endl;
		cout << "line #" << i << ": " << lines[i] << endl; // print out the string at this location
	}
}



// 3. Enter new lines of code to the end of the program
void Interface::appendLines()
{
	string myString;
	bool test = false;

	cout << "Please enter the string you would like to save. \n"
		<< "NOTE: enter a . in order to end this function. \n";
	while (test == false)
	{
		getline(cin, myString); // enter in the string
		if (myString == ".") // this loop will continue until a . is entered
		{
			test = true; // end this loop if a . is entered
		}
		if ((myString != "") && (myString != "."))
		{
			lines.insert(lines.end(), myString); // insert the string entered to the end of the vector
		}
	}
}


// 4. Insert new lines before an existing line
void Interface::insertLines()
{	
	string myString;
	int lineNumber;
	bool testing = false;
	while (testing == false)
	{
		cout << "Please enter the number of the string you would like to enter before. \n"
			<< "NOTE: For the number you enter, the string you will insert will come before this line \n";
		cin >> lineNumber; // write in the line number the user wants to put the new lines before
		if (lineNumber < 0)
		{
			cout << "You have entered an improper number. Please try again. \n";
		}
		else
		{
			testing = true;
		}
	}
		cout << "Please enter the string you would like to save. \n"
			<< "NOTE: enter a . in order to end this function. \n";
	bool test = false;
	while (test == false)
	{
		getline(cin, myString);
		if (myString == ".") // this loop will continue until a . is entered
		{
			test = true; // end this loop if a . is entered
		}
		if ((myString != "") && (myString != "."))
		{
			lines.insert(lines.begin() + lineNumber, myString); // insert the string entered to the end of the vector
		}
	}
}


// 5. Delete a range of existing line
void Interface::deleteLines()
{
	int begLinDel;
	int endLinDel;
	bool testing = false;
	while (testing == false)
	{
		cout << "Please enter the beginning line you would like to delete from. \n";
		cin >> begLinDel;

		if (begLinDel < 0)
		{
			cout << "You have entered an improper number. Please try again. \n";
		}
		else
		{
			testing = true;
		}
	}

	testing = false;

	while (testing == false)
	{
		cout << "Please enter the ending line you would like to delete to. \n";
		cin >> endLinDel;

		if (endLinDel < 0)
		{
			cout << "You have entered an improper number. Please try again. \n";
		}
		else
		{
			testing = true;
		}
	}
	lines.erase(lines.begin() + begLinDel, lines.begin() + endLinDel);
	cout << "These lines have been deleted. \n";
}


// 6. Replace the contents of an existing line
void Interface::replaceOneLine()
{
	string myString;
	int lineNumber;
	bool testing = false;

	while (testing == false)
	{
		cout << "Please enter the number of the string you would like to enter before. \n"
			<< "NOTE: For the number you enter, the string you will insert will come before this line \n";
		cin >> lineNumber; // write in the line number the user wants to put the new lines before

		if (lineNumber < 0)
		{
			cout << "You have entered an improper number. Please try again. \n";
		}
		else
		{
			testing = true;
		}
	}
	lines.erase(lines.begin() + lineNumber);
	cout << "Please enter the string you would like to save. \n"
		<< "NOTE: enter a . in order to end this function. \n";
	cin.ignore(10000, '\n');
	getline(cin, myString);
	lines.insert(lines.begin() + lineNumber, myString);
}


// 7. Save program to a file
void Interface::saveProgramIntoFile()
{
	string fileName;
	cout << "Name of file to download program to (ex. file.txt): ";
	cin >> fileName;
	ofstream outFile;
	outFile.open(fileName);
	for (unsigned int i = 0; i < lines.size(); i++) // loop to call every string in the vector
	{
		outFile << lines[i] << endl;
	}
	outFile.close();
}

//An auxilliary message displaying function
void Interface::endOfService(const string service)
{
	cout<<endl << service << " done." << endl << "Press any key to continue.";
	_getch();
	cout << endl;
	cout << "****************************************************" <<endl<< endl;

}

// This menu() function is the interface
void Interface::startInterface() {

	vectOfTokenVects myVectOfTokenVects;
	vectOfCategoryVects myVectOfCategoryVects;

	// "Then I suppose now is the time for me to say something profound....
	// Nothing comes to mind. Let's do it."
	bool inMenu = true;	// while the user is using the program this var is set to true and the menu keeps looping.
						// when the user wants to quit, it is set to false and the loop ends.
	char keyPressed;	// This var stores which menu selection the user picks.

	string infixRaw; // string to contain infix for function C
	expVector infixExp, postfixExp; // infix and postfix for function C
	floatVarValueTable varTable; // used for function C
	bool round = true; // this is the bool to keep the loop going in function C
	float expValue; // used in function C

	while ( inMenu )
	{
		cout<< endl << endl << endl;
		cout << "****************************************************" << endl;
		cout  <<"**  MENU:(press a character to select an option)  **" << endl;
 		cout << "****************************************************" << endl;
		cout<<"Q. [QUIT]     Quit."<<endl;
		cout<<"L. [LOAD]     Read in a program (lines of statements) from a file"<<endl;
  		cout<<"S. [SAVE]     Save lines of statement as a program into a file"<<endl;
		cout << endl;

		cout<<"D. [DISPLAY]  Display the source code as lines of statements"<<endl;
		cout <<"N. [LEXICAL ANALYSIS] Perform lexical analysis on the lines of"
			<< "statements.\n";
		cout << endl;

		cout<<"A. [APPEND]   Append new lines to the end of the program"<<endl;
		cout<<"I. [INSERT]   Insert new lines before an existent line"<<endl;
		cout<<"X. [DELETE]   Delete a range of existent lines"<<endl;
		cout<<"R. [REPLACE]  Replace the contents of an existent line"<<endl;
		cout<<"C. [CALCULATOR] evaluates arithmetic or logic expressions involving \n"
			"only numerical constants, parentheses, and arithmetic or logical operators"<<endl;
		cout << endl;

		cout<<"P. [PARSE]    Parse and ident the code" << endl;
		cout<<"E. [EXECUTE]  Execute (run) the program"<<endl;
		cout<<"T. [TOGGLE]   Toggle the execution debug mode"<<endl;

		cout << "****************************************************" <<endl<< endl;

		cout<<"Your choice is: ";
		keyPressed = _getch();
		cout<<keyPressed << endl;

		switch(keyPressed) {
		case 'Q': case 'q'://Quit
			cout << "[QUIT]:" << endl;
			inMenu = false;
			break;

		case 'L': case 'l':// 1. Read in a program (lines of statements) from a file
 			cout << "[LOAD PROGRAM]:" << endl;
			loadProgramFromFile();
			endOfService("[LOAD PROGRAM]");
			break;

		case 'D': case 'd':// 2. Display the lines of statements
			cout << "[DISPLAY PROGRAM]:" << endl;
			displayProgram();
			endOfService("[DISPLAY PROGRAM]");
			break;

		case 'N': case 'n': // Perform Lexical Analysis on the lines of statements
			cout << "[LEXICAL ANALYSIS]:" << endl;
			for (size_t i = 0; i < lines.size(); i++)
			{
				cout << "Line["
					<< i
					<< "].\t"
					<< lines[i]
					<< endl;
			}
				cout << endl << "Lexical analysis of the program line by line." << endl << endl;
			//Get the lexical information 
			LexicalScanner::getLexicalInfo(
				lines,
				myVectOfTokenVects,
				myVectOfCategoryVects);

			//Display the lexical information 
			LexicalScanner::displayLexicalInfo(
				myVectOfTokenVects,
				myVectOfCategoryVects);
			break;

		case 'C': case 'c':
			cout << "[CALCULATOR]:" << endl;
			while (round == true)
			{
				cout << "\n Please enter an infix using numerical constants, parentheses, and \n"
					"arithmetic or logical operators or press . to leave this function. \n";
				getline(cin, infixRaw);

				if (infixRaw == ".")
				{
					round = false;
				}

				infixExp.clear();
				postfixExp.clear();

				LexicalScanner::getPerLineTokenVectFromOneStringObject (infixRaw, infixExp);
				ExpressionEvaluator::infixToPostfixConversion(infixExp, postfixExp);
				cout << "Tokens of this postfix expression:" << endl;
				for (expVector::iterator pos = postfixExp.begin(); pos != postfixExp.end(); pos++)
					cout << '\t' << *pos << endl;

				if (ExpressionEvaluator::postfixEvaluator(postfixExp, varTable, expValue))
					cout << "The value of this expression is " << expValue << endl;
				else
					cout << "This expression is not a valid expression" << endl;

			}
			break;

		case 'A': case 'a':// 3. Append new lines of code to the end
			cout << "[APPEND]:" << endl;
			appendLines();
			endOfService("[APPEND LINES]");
			break;

		case 'I': case 'i':// 4. Insert a new line after an existing line
			cout << "[INSERT LINES]:" << endl;
			insertLines();
			endOfService("[INSERT LINES]");
			break;

		case 'X': case 'x':// 5. Delete an existing line
			cout << "[DELETE LINES]:" << endl;
			deleteLines();
			endOfService("[DELETE LINES]");
			break;

		case 'R': case 'r':// 6. Replace the contents of an existing line
			cout << "[REPLACE]:" << endl;
			replaceOneLine();
			endOfService("[REPLACE ONE LINE]");
			break;

		case 'S': case 's':// 7. Save program to a file
			cout << "[SAVE]:" << endl;
			saveProgramIntoFile();
			endOfService("[SAVE CODE INTO A FILE]");
			break;

		case 'P': case 'p':// 8. Parse and Indent the program
			cout << "[PARSE AND INDENT SOURCE CODE]:" << endl;
			endOfService("[PARSE AND INDENT SOURCE CODE]");
			break;

		case 'E': case 'e':// 9. Run program
			cout << "[EXECUTE TO RUN PROGRAM]:" << endl;
			interpreter::interpHome(lines);
			endOfService("[EXECUTE TO RUN PROGRAM]");
			break;

		case 'T': case 't':// Toggle the debug mode
			cout << "[TOGGLE the debug mode]:" << endl;
			break;


		default:
			cout << "[?? UNKNOWN COMMAND]:" << endl;
			// Unrecognized key, do nothing
			break;
		}

	} // End of while loop.
}
