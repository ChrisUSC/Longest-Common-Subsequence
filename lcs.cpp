/*
 * Implementation of Longest Common Subsequence
 * Posted for CSCI 270 at USC, Fall semester 2018

 * Ideally, you will reference this along with 
 * your lecture notes from Lecture 8, September17-18
 
 * Most of the file isn't sufficiently commented
 * as it assumes that as parallel reading.
 *
 * Compile as
 	>g++ -std=c++11 lcs.cpp
 */

#include <fstream>
#include <iostream>
#include <stack>
#include <string>
#include <vector>

using namespace std;

void lcs_by_file(char * filename);
int lcs(string x, string y, bool output=false);



int main ( int argc, char *argv[] )
{
	if (argc <= 1 )
	{
		/* TODO:  Output how to use this.
		 */
		cout << "Usage:"<< endl; 
		cout << "Zero command-line parameters: print this message." << endl;
		cout << "One command-line parameter:  provide a file to check all interesting pairs." << endl;
		cout << "Two command-line parameters:  find LCS of those two strings." << endl;
		return 0;
	}
	if ( argc == 2)
	{
		/*
		 If you want to find all "interesting" pairs
		 of LCS within a file (for some definition of
		 interesting), call with one parameter, a file 
		 words, one per line.

		 Right now, the defintion of interesting is all words.
		 There is an if(true) in the code there you can replace
		 with a check for your definition of interesting.

		 It also only outputs them if the lcs is >3 and <6
		 (the latter to avoid things like lcs("homerun", "homeruns") = "homerun")
		 */
		lcs_by_file( argv[1] );
		
		return 0;
	}
	if (argc == 3 )
	{
		cout << lcs(argv[1], argv[2], true) << endl;
		return 0;
	}
	return 0;
}

void lcs_by_file(char * filename)
{
	ifstream fs(filename);
	vector<string> words;
	for(string line; getline(fs, line); )
	{
		words.push_back(line);
	}
	int i,j;
	for (i=0; i < words.size(); i++)
	{
		if (true) // you can replace this with some definition of "interesting"
		{

			for (j=i+1; j < words.size(); j++)
			{
				if (true) // you can replace this with some definition of "interesting"
				{
					int l = lcs(words[i], words[j]);
					// or if we find some other way to describe "interesting" pairs.
					if ( l > 3 && l < min(words[i].size(), words[j].size() ) && l < 6)
					{
						cout << words[i] << "\t" << words[j] << "\t";
						lcs(words[i], words[j], true);
					}
				}
			}
		}
	}
}

int lcs(string x, string y, bool output)
{
	vector< vector<int>> memo(x.size() + 1,  vector<int>( y.size() + 1));
	int i,j;
	for (i=0; i <= x.size(); i++)
	{
		memo[i][0] = 0;
	}
	for (j=0; j <= y.size(); j++)
	{
		memo[0][j] = 0;
	}
	for (i=1; i <= x.size(); i++)
	{
		for (j=1; j<= y.size(); j++)
		{
			if (x[i-1] == y[j-1])
				memo[i][j] = 1 + memo[i-1][j-1];
			else
				memo[i][j] = max( memo[i-1][j], memo[i][j-1]);
		}
	}

	if(output)
	{
		stack<char> st;
		i = x.size(); j = y.size();
		while( i > 0 )
		{
			if (x[i-1] == y[j-1])
			{
				st.push(x[i-1]);
				i--; j--;
			}
			else
			{
				if (memo[i][j] == memo[i-1][j])
					i--;
				else
					j--;
			}
		}
		while( ! st.empty () )
		{
			cout << st.top();
			st.pop();
		}
		cout << endl;
	}

	return memo[x.size()][y.size()];
}
