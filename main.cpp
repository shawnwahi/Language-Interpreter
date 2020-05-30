/*
 * main.cpp
 *
 * CS280 - Spring 2020
 * Lexical Analyzer test engine
 */

#include <fstream>
using std::ifstream;

#include <map>
using std::map;

#include "lex.h"
#include "parse.h"

using std::cin;
using std::cout;
using std::cerr;
using std::endl;

int
main(int argc, char *argv[])
{
	int lineNumber = 0;

	Tok	tok;

	istream *in = &cin;
	ifstream file;

	for( int i=1; i<argc; i++ ) {
		string arg( argv[i] );
		if( in != &cin ) {
			cerr << "ONLY ONE FILE NAME ALLOWED" << endl;
			return 0;
		}
		else {
			file.open(arg);
			if( file.is_open() == false ) {
				cerr << "CANNOT OPEN " << arg << endl;
				return 0;
			}

			in = &file;
		}
	}
    
    Pt *tree = Prog(*in, lineNumber);
    
    if( tree == 0 )
        return 0;
    
//Make sure that a variable has been assigned to (using EQ) before it is used. If you find a variable that was not assigned to, print UNDECLARED VARIABLE followed by a space and the variable name

    cout << "PLUS COUNT: " << tree->Traverse(&Pt::isPlus) << endl;
    cout << "EQ COUNT: " << tree->Traverse(&Pt::isEq) << endl;
	cout << "MAX DEPTH: " << tree->MaxDepth() << endl;

	return 0;
}
