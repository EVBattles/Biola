#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <cctype>
#include <cstring>
#include <iomanip>

using namespace std;

void writeIn(vector<string> & grammar, vector<char> & hold)
{
	// Write in rules
	char lead;
	string rule;
	char moreRules = 'Y';

	// Opening comments
	cout << "Welcome to Program number 5. \n";
	cout << "If you have another rule to enter, please press Y. \n";
	cout << "If not, please press N \n \n";

	// Rule Entry
	while ((moreRules == 'Y') || (moreRules == 'y'))
	{
		rule.clear();
		cout << "enter a rule: ";
		cin >> lead;
		cin >> rule;
		//cout << lead << " " << rule << endl;
		hold.push_back(lead); // save input lead to hold vector
		grammar.push_back(rule); // save input rule string to grammar vector
		cout << endl;
		cout << "more rules? ";
		cin >> moreRules;
		cout << endl;

		//cout << "Printing \n";
		//for (int r = 0; r < hold.size(); r++)
		//{
		//	cout << hold[r] << " " << grammar[r] << endl;
		//}

	}
}

void search(vector <string> & grammar, vector <char> & hold, vector <char> & term, vector <char> & nonTerm)
{
	// search through rules for terminal and non terminal symbols
	// NOTE: rows will be labled by nonterm and term
	// NOTE: columns will be labled by term only

	bool existsT = false;
	bool existsN = false;

	for (int f = 0; f < grammar.size(); f++) // iterating grammar strings
	{
		for (int r = 0; r < grammar[f].size(); r++) // iterating grammar chars
		{
			if (islower(grammar[f][r])) // if lowercase
			{
				for (int g = 0; g < term.size(); g++) // iterating terminal
				{
					if (grammar[f][r] == term[g]) // if already in terminal
					{
						existsT = true; // set to true
					}
				}
				if (existsT == false) // if does not exist in terminal
				{
					term.push_back(grammar[f][r]); // push into terminal
				}
			}
			else if (isupper(grammar[f][r])) // if uppercase
			{
				for (int t = 0; t < nonTerm.size(); t++) // iterating nonterminal
				{
					if (grammar[f][r] == nonTerm[t]) // if already exists in nonterminal
					{
						existsN = true; // set to true
					}
				}
				if (existsN == false) // if does not exist in terminal
				{
					nonTerm.push_back(grammar[f][r]); // push into nonterminal
				}
			}

		}
	}
}

void tableColumn(vector <char> & term, vector <char> & nonTerm, string table[20][15])
{
	// set the 0 column to terminal and nonterminal labels
	int count = 1;
	for (int w = 0; w < nonTerm.size(); w++)
	{
		table[0][count] = nonTerm[w];
		count++;
	}

	for (int x = 0; x < term.size(); x++)
	{
		table[0][count] = term[x];
		count++;
	}

	table[0][count] = "BOS";
}

void tableRow(vector <char> & term, string table[20][15])
{
	// set the 0 row to terminal labels
	int count = 1;
	for (int e = 0; e < term.size(); e++)
	{
		table[count][0] = term[e];
		count++;
	}

	table[count][0] = "EOIS";
}

void stepTwo(vector <char> & term, 
	string table[20][15], vector <string> & grammar, 
	vector <char> & hold, vector <char> & nonTerm)
{
	// set A -> a& cells
	string begin = "rep(";
	string end = "),retain";
	string rammarg; // reverse grammar string
	for (int q = 0; q < nonTerm.size(); q++) // iterate nonTerm
	{
		for (int a = 0; a < term.size(); a++) // iterate term
		{
			for (int z = 0; z < hold.size(); z++) // iterate through the rules
			{
				if ((hold[z] == nonTerm[q]) && (grammar[z][0] == term[a])) // if the hold = the nonterm and the grammar = the term
				{
					for (int o = grammar[z].size() - 1; o > -1; o--) // reverse the order of the grammar
					{
						rammarg.push_back(grammar[z][o]); // push this grammar chart to the end of rammarg string
					}

					table[a + 1][q + 1] = begin + rammarg + end; // set the table to "rep("rammarg"),retain"
					rammarg.clear();
				}
			}
		}
	}
}

void stepThree(vector <char> & columnLabels, vector <char> & term, string table[20][15])
{
	// set the two same terminals intersection of the table
	string bothLower = "pop,advance";
	for (int y = 0; y < columnLabels.size(); y++) // iterate columnLabels
	{
		for (int m = 0; m < term.size(); m++) // iterate term
		{
			if (columnLabels[y] == term[m]) // if both columnLabels and term are both lowercase
			{
				table[m + 1][y + 1] = bothLower; // set that point in the table to bothLower
			}
		}
	}

}

void stepFour(string table[20][15], vector <char> & term, vector <char> & nonTerm)
{
	//set bottom marker and end marker intersection with accept
	table[term.size() + 1][term.size() + nonTerm.size() + 1] = "accept";
}

void stepFive(vector <char> & columnLabels, vector <char> & term, string table[20][15])
{
	// set the rest to reject
	for (int t = 0; t < columnLabels.size() + 2; t++) // iterate columnLabels
	{
		for (int u = 0; u < term.size() + 2; u++) // iterate term
		{
			if (table[u][t] == "") // if table at this point is empty
			{
				table[u][t] = "reject"; // set this point in the table to reject
			}
		}
	}
	table[0][0] = "";
}

void print(vector <char> & term, vector <char> & columnLabels, string table[20][15])
{
	// print out table
	for (int n = 0; n < columnLabels.size() + 2; n++) // iterate columnLabels
	{
		for (int w = 0; w < term.size() + 2; w++) // iterate term
		{
			cout << setw(20) << table[w][n] << " "; // print out table information
		}
		cout << endl;
	}
}

void main()
{
	// main function - mainly calls everything
	vector <string> grammar; // input grammar
	vector <char> hold; // input source character
	vector <char> term; // list of all term types - also row labels
	vector <char> nonTerm; // list of all nonterm types
	vector <char> columnLabels; // list of column labels
	// declaration of array
	string table[20][15];
	char end;
	
	// write in grammar rules
	writeIn(grammar, hold); // *******************************************************
	//cout << "Printing \n";
	//for (int r = 0; r < hold.size(); r++)
	//{
	//	cout << hold[r] << " " << grammar[r] << endl;
	//}
	// ***************************************************************Step 1****************************************************************
	// set up table
	// search strings to find terms and nonterms
	search(grammar, hold, term, nonTerm); // *******************************************
	// set the first column to term and nonterms
	tableColumn(term, nonTerm, table); // *******************************************************
	// set the first row to term
	tableRow(term, table); // *******************************************************
	// ***************************************************************Step 2****************************************************************
	// set the A->a& of the table
	stepTwo(term, table, grammar, hold, nonTerm);
	// ***************************************************************Step 3****************************************************************
	// set the two same terminals intersection of the table
	// declare a vector string of column labels
	for (int c = 0; c < nonTerm.size(); c++)
	{
		columnLabels.push_back(nonTerm[c]);
	}
	for (int h = 0; h < term.size(); h++)
	{
		columnLabels.push_back(term[h]);
	}
	stepThree(columnLabels, term, table);
	// ***************************************************************Step 4****************************************************************
	// set bottom marker and end marker intersection with accept
	stepFour(table, term, nonTerm);
	// ***************************************************************Step 5****************************************************************
	// set the rest to reject
	stepFive(columnLabels, term, table);
	// ***************************************************************Print Out*************************************************************
	// print out the table in correct format
	cout << "Table \n \n";
	print(term, columnLabels, table);
	cout << "\n \n";

	cout << "Press any key to end this program. \n";
	cin >> end;
}