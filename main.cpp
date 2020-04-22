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

	bool vflag = false;
	bool idsflag = false;
	bool icflag = false;
	bool scflag = false;

	int tokCount = 0;
	map<string,bool> identifiers;
	map<string,bool> strings;
	map<int,bool> ints;

	for( int i=1; i<argc; i++ ) {
		string arg( argv[i] );
		if( arg == "-v" )
			vflag = true;
		else if( arg == "-ids" )
			idsflag = true;
		else if( arg == "-iconsts" )
			icflag = true;
		else if( arg == "-sconsts" )
			scflag = true;
		else if( arg[0] == '-' ) {
			cerr << "UNRECOGNIZED FLAG " << arg << endl;
			return 0;
		}
		else if( in != &cin ) {
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

	while( (tok = getNextToken(*in, lineNumber)) != DONE && tok != ERR ) {
		if( vflag )
			cout << tok << endl;

		++tokCount;
		if( tok == SCONST ) {
			strings[ tok.GetLexeme() ] = true;
		}
		else if( tok == ICONST ) {
			ints[ stoi(tok.GetLexeme()) ] = true;
		}
		else if( tok == IDENT ) {
			identifiers[ tok.GetLexeme() ] = true;
		}
	}

	if( tok == ERR ) {
		cout << "Error on line " << tok.GetLinenum()+1 << " (" << tok.GetLexeme() << ")" << endl;
		return 0;
	}

	// summary
	cout << "Lines: " << lineNumber << endl;
	if( lineNumber == 0 )
		return 0;

        cout << "Tokens: " << tokCount << endl;

	if( scflag ) {
		if( strings.size() > 0 ) {
			    cout << "STRINGS:" << endl;
		    for( const auto& sp : strings )
			cout << sp.first << endl;
		}
        }

	if( icflag ) {
		if( ints.size() > 0 ) {
			    cout << "INTEGERS:" << endl;
		    for( const auto& sp : ints )
			cout << sp.first << endl;
		}
	}

	if( idsflag ) {
		if( identifiers.size() > 0 ) {
			cout << "IDENTIFIERS: ";
			auto it = identifiers.begin();
			cout << it->first;

			for( it++; it != identifiers.end(); it++ )
				cout << ", " << it->first;
			cout << endl;
		}
	}
    
	return 0;
}
