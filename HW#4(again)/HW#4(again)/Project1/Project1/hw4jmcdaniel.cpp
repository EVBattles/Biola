#include <iostream>
#include <string>
#include <vector>

using namespace std;

vector <char> bucket; // stack container
vector <char> postfix; // postfix container
string infix; // infix container
bool accept = false; // notification of accepted for conclusion
bool one = false; // notification for retaining action 1
bool two = false; // notification for retaining action 2
bool three = false; // notification for retaining action 3
bool fatal = false; // notification for fatal error and termination


void stateOne(char infix1) // state one
{
	//cout << "State One " << infix1 << endl;;
	switch (infix1)
	{
	case '0': case '1': case '2': case '3': case '4': 
	case '5': case '6': case '7': case '8': case '9':
		//cout << "Number \n";
		switch (bucket.back())
		{
		case 'E':// number
			//cout << "straight number \n";
			// reject *
			fatal = true;
			infix.clear();
			return;

			break;
		case 'e':// number on top of a plus
			//cout << "number on top of plus \n";
			// reject *
			fatal = true;
			infix.clear();
			return;

			break;
		case 'L':// left parenthases
			//cout << "( \n";
			// push(E) *
			// out(a) *
			bucket.push_back('E');
			postfix.push_back(infix1);
			break;
		case 'l':// left parenthases on top of a plus
			//cout << "( on top of + \n";
			// push(E) *
			// out(a) *
			bucket.push_back('E');
			postfix.push_back(infix1);
			
			break;
		case 's':// left parenthases on top of a *
			//cout << "( on top of * \n";
			// push(E) *
			// out(a) *
			bucket.push_back('E');
			postfix.push_back(infix1);

			break;
		case '+':
			//cout << "+ \n";
			// push(e) *
			// out(a) *
			bucket.push_back('e');
			postfix.push_back(infix1);

			break;
		case '*':
			//cout << "* \n";
			// pop *
			// out(a*) *
			bucket.pop_back();
			postfix.push_back(infix1);
			postfix.push_back('*');

			break;
		case 'x': // end of bucket.back()
			//cout << "end of bucket \n";
			// push(E)
			// out(a)
			bucket.push_back('E');
			postfix.push_back(infix1);

			break;
		default:
			cout << "Do not recognize this symbol: " << bucket.back() << endl;;
			fatal = true;
			infix.clear();
			break;
		}
		break;
	case '+':
		//cout << "+ \n";
		switch (bucket.back())
		{
		case 'E':// number
			//cout << "E \n";
			//push(+)
			bucket.push_back('+');

			break;
		case 'e':// number on top of a plus
			//cout << "e \n";
			// pop
			// out(+)
			bucket.pop_back();
			postfix.push_back('+');

			break;
		case 'L':// left parenthases
			//cout << "L \n";
			// reject
			fatal = true;
			infix.clear();
			return;

			break;
		case 'l':// left parenthases on top of a plus
			//cout << "l \n";
			// reject
			fatal = true;
			infix.clear();
			return;

			break;
		case 's':// left parenthases on top of a *
			//cout << "s \n";
			// reject
			fatal = true;
			infix.clear();
			return;

			break;
		case '+':// plus
			//cout << "+ \n";
			// reject
			fatal = true;
			infix.clear();
			return;

			break;
		case '*':// multiply
			//cout << "* \n";
			// reject
			fatal = true;
			infix.clear();
			return;

			break;
		case 'x':// end of bucket.back()
			//cout << "x \n";
			// reject
			fatal = true;
			infix.clear();
			return;

			break;
		default:
			cout << "Do not recognize this character: " << bucket.back() << endl;
			fatal = true;
			infix.clear();
			break;
		}
		break;
	case '*':
		//cout << "* \n";
		switch (bucket.back())
		{
		case 'E':// number
			//cout << "E \n";
			// push(*)
			bucket.push_back('*');

			break;
		case 'e':// number on top of a plus
			//cout << "e \n";
			// push(*)
			bucket.push_back('*');

			break;
		case 'L':// left parenthases
			//cout << "L \n";
			// reject
			fatal = true;
			infix.clear();
			return;

			break;
		case 'l':// left parenthases on top of a plus
			//cout << "l \n";
			// reject
			fatal = true;
			infix.clear();
			return;

			break;
		case 's':// left parenthases on top of a *
			//cout << "s \n";
			// reject
			fatal = true;
			infix.clear();
			return;

			break;
		case '+':// plus
			//cout << "+ \n";
			// reject
			fatal = true;
			infix.clear();
			return;

			break;
		case '*':// multiply
			//cout << "* \n";
			// reject
			fatal = true;
			infix.clear();
			return;

			break;
		case 'x':// end of bucket.back()
			//cout << "x \n";
			// reject
			fatal = true;
			infix.clear();
			return;

			break;
		default:
			cout << "Do not recognize this symbol: " << bucket.back() << endl;
			fatal = true;
			infix.clear();
			break;
		}
		break;
	case '(':
		//cout << "( \n";
		switch (bucket.back())
		{
		case 'E':// number
			//cout << "E \n";
			// reject
			fatal = true;
			infix.clear();
			return;

			break;
		case 'e':// number on top of a plus
			//cout << "e \n";
			// reject
			fatal = true;
			infix.clear();
			return;

			break;
		case 'L':// left parenthases
			//cout << "L \n";
			// push(L)
			bucket.push_back('L');

			break;
		case 'l':// left parenthases on top of a plus
			//cout << "l \n";
			// push(L)
			bucket.push_back('L');

			break;
		case 's':// left parenthases on top of a *
			//cout << "s \n";
			// push(L)
			bucket.push_back('L');

			break;
		case '+':// plus
			//cout << "+ \n";
			// push(l)
			bucket.push_back('l');

			break;
		case '*':// multiply
			//cout << "* \n";
			// push(s)
			bucket.push_back('s');

			break;
		case 'x':// end of bucket.back()
			//cout << "x \n";
			// push(L)
			bucket.push_back('L');

			break;
		default:
			cout << "Do not recognize this symbol: " << bucket.back() << endl;
			fatal = true;
			infix.clear();
			break;
		}
		break;
	case ')':
		//cout << ") \n";
		switch (bucket.back())
		{
		case 'E':// number
			//cout << "E \n";
			// pop
			// retain S3
			bucket.pop_back();
			three = true;

			break;
		case 'e':// number on top of a plus
			//cout << "e \n";
			// pop
			// retain S2
			bucket.pop_back();
			two = true;

			break;
		case 'L':// left parenthases
			//cout << "L \n";
			// reject
			fatal = true;
			infix.clear();
			return;

			break;
		case 'l':// left parenthases on top of a plus
			//cout << "l \n";
			// reject
			fatal = true;
			infix.clear();
			return;

			break;
		case 's':// left parenthases on top of a *
			//cout << "s \n";
			// reject
			fatal = true;
			infix.clear();
			return;

			break;
		case '+':// plus
			//cout << "+ \n";
			// reject
			fatal = true;
			infix.clear();
			return;

			break;
		case '*':// multiply
			//cout << "* \n";
			// reject
			fatal = true;
			infix.clear();
			return;

			break;
		case 'x':// end of bucket.back()
			//cout << "x \n";
			// reject
			fatal = true;
			infix.clear();
			return;

			break;
		default:
			cout << "Do not recognize this symbol: " << bucket.back() << endl;
			fatal = true;
			infix.clear();
			break;
		}
		break;
	case 'G':
		//cout << "G \n";
		switch (bucket.back())
		{
		case 'E':// number
			//cout << "E \n";
			// pop
			// retain S1
			bucket.pop_back();
			one = true;

			break;
		case 'e':// number on top of a plus
			//cout << "e \n";
			// pop
			// retain S2
			bucket.pop_back();
			two = true;
			cout << two << endl;

			break;
		case 'L':// left parenthases
			//cout << "L \n";
			// reject
			fatal = true;
			infix.clear();
			return;

			break;
		case 'l':// left parenthases on top of a plus
			//cout << "l \n";
			// reject
			fatal = true;
			infix.clear();
			return;

			break;
		case 's':// left parenthases on top of a *
			//cout << "s \n";
			// reject
			fatal = true;
			infix.clear();
			return;

			break;
		case '+':// plus
			//cout << "+ \n";
			// reject
			fatal = true;
			infix.clear();
			return;

			break;
		case '*':// multiply
			//cout << "* \n";
			// reject
			fatal = true;
			infix.clear();
			return;

			break;
		case 'x':// end of bucket.back()
			//cout << "x \n";
			// accept
			bucket.pop_back();
			accept = true;
			return;

			break;
		default:
			cout << "Do not recognize this symbol: " << bucket.back() << endl;
			fatal = true;
			infix.clear();
			break;
		}
		break;
	default:
		cout << "Do not recognize this symbol: " << infix1 << endl;
		fatal = true;
		infix.clear();
		break;
	}
	return;
}

void stateTwo(char infix1) // state two
{
	//cout << "State Two \n";
	switch (infix1)
	{
	case ')':
		//cout << ") \n";
		switch (bucket.back())
		{
		case '+':

			// pop
			// out(+)
			// retain S3
			bucket.pop_back();
			postfix.push_back('+');
			three = true;

			break;
		case '*':
			//cout << "* \n";
			// pop
			// out(+)
			// retain S1
			bucket.pop_back();
			postfix.push_back('*');
			one = true;

			break;
		default:
			cout << "Do not recognize this symbol: " << bucket.back() << "with: " << infix1 << endl;
			fatal = true;
			infix.clear();
			break;
		}
		break;
	case 'G':
		//cout << "G \n";
		switch (bucket.back())
		{
		case '+':
			//cout << "+ \n";
			// pop
			// out(+)
			// retain S1
			bucket.pop_back();
			postfix.push_back('+');
			one = true;

			break;
		case '*':
			//cout << "* \n";
			// reject
			fatal = true;
			infix.clear();
			return;

			break;
		default:
			cout << "Do not recognize this symbol: " << bucket.back() << "with: " << infix1 << endl;
			fatal = true;
			infix.clear();
			break;
		}
		break;
	default:
		cout << "Do not recognize this symbol: " << infix1 << endl;
		fatal = true;
		infix.clear();
		break;
	}
	return;
}

void stateThree(char infix1) // state three
{
	//cout << "State Three \n";
	switch (infix1)
	{
	case ')':
		//cout << ") \n";
		switch (bucket.back())
		{
		case 'L':
			//cout << "L \n";
			// Rep(E)
			// retain S1
			bucket.pop_back();
			bucket.push_back('E');

			break;
		case 'l':
			//cout << "l \n";
			// Rep(E)
			// retain S1
			bucket.pop_back();
			bucket.push_back('E');
			one = true;

			break;
		case 'E':
			//cout << "E \n";
			// pop
			// retain S3
			bucket.pop_back();
			three = true;

			break;
		case 's':
			//cout << "s \n";
			// pop 
			// retain S2
			bucket.pop_back();
			two = true;

			break;
		case 'x':
			//cout << "x 1\n";
			// reject
			fatal = true;
			infix.clear();
			//cout << "Clear infix \n";
			return;
			break;
		}
		break;
	default:
		cout << "Do not recognize this symbol: " << infix1 << endl;
		fatal = true;
		infix.clear();
		break;
	}
	return;
}

void main()
{

	bucket.push_back('x'); // end of bucket.back() indicator

	cout << "Please enter the infix you would like to use. \n";
	getline(cin, infix);

	for (int i = 0; i < infix.size(); i++)
	{
		//cout << "one: " << one << ", two: " << two << ", three: " << three << endl;
		if ((infix[i] != ' ') && (!infix.empty()))
		{
			if (fatal) // if the fatal error bool is triggered, go straight to output
			{
				i = infix.size(); // set i to infix size to end the loop
				infix.clear(); // clear the infix to reduce error
			}
			else // if the fatal error bool has not triggered, continue on with code
			{
				stateOne(infix[i]);
				while ((one) || (two) || (three)) // if one or two or three have been triggered
				{
					if ((one == true) && (!fatal)) // if one is true
					{
						one = false; // set one back to false for reuse
						stateOne(infix[i]); // call stateOne with infix[i]
					}
					else if ((two == true) && (!fatal)) // if two is true
					{
						two = false; // set two back to false for reuse
						stateTwo(infix[i]); // call stateTwo with infix[i]
					}
					else if ((three == true) && (!fatal)) // if three is true
					{
						three = false; // set three back to false for reuse
						stateThree(infix[i]); // call stateThree with infix[i]
					}
				}
			}
		}

		//cout << endl;
		//for (int f = 0; f < bucket.size(); f++)
		//{
		//	cout << bucket[f];
		//}
		//cout << endl << endl;

	}

	//char g;
	//cout << "Entering G loop \n";

	//for (int f = 0; f < bucket.size(); f++)
	//{
	//	cout << bucket[f];
	//}
	//cout << endl << endl;

	//cin >> g;

	// G loop

	while ((bucket.size() > 0) && (fatal == false)) // while the bucket still contains data and fatal is false
	{
		//cout << "one: " << one << ", two: " << two << ", three: " << three << endl;
		if ((one == false) && (two == false) && (three == false)) // if all three are false
		{
			stateOne('G'); // call stateOne with G
		}
		else if (one == true) // if one is true
		{
			one = false; // set one back to false for reuse
			stateOne('G'); // call stateOne with G
		}
		else if (two == true) // if two is true
		{
			two = false; // set two back to false for reuse
			//cout << "Setting two to false \n";
			stateTwo('G'); // call stateTwo with G
		}
		else if (three == true) // if three is true
		{
			three = false; // set three back to false for reuse
			stateThree('G'); // call stateThree with G
		}

		//cout << endl;
		//for (int f = 0; f < bucket.size(); f++)
		//{
		//	cout << bucket[f];
		//}
		//cout << endl << endl;
		//cin >> g;
	}
	
	if (accept == true) // if accept is true, print out accept message and print postfix
	{
		cout << "Accepted \n";
		for (int f = 0; f < postfix.size(); f++)
		{
			cout << postfix[f];
		}
		cout << endl << endl;
	}
	else // if accept is still false, print out improper infix error message and print postfix
	{
		cout << "This is an improper infix. \n";
		for (int f = 0; f < postfix.size(); f++)
		{
			cout << postfix[f];
		}
		cout << endl << endl;
	}
	char c;
	cout << "Enter any letter to quit. \n";
	cin >> c;

}