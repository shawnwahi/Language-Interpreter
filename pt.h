/*
 * pt.h
 */

#ifndef PT_H_
#define PT_H_

#include <iostream>
#include <vector>
#include <map>
#include <string>

using std::vector;
using std::map;
using std::string;
using std::cin;
using std::cout;
using std::cerr;
using std::endl;

#include "parse.h"
#include "lex.h"

// NodeType represents all possible types
enum NodeType { ERRTYPE, INTTYPE, STRTYPE };

class Pt {
protected:
	int			linenum;
	Pt	*left;
	Pt	*right;

public:
	Pt(int linenum, Pt *l = 0, Pt *r = 0)
		: linenum(linenum), left(l), right(r) {}

	virtual ~Pt() {
		delete left;
		delete right;
	}

	int GetLineNumber() const { return linenum; }

	int Traverse(bool (Pt::*func)(void) const) const {
        int cnt = 0;
		if( left ) cnt += left->Traverse(func);
		if( right ) cnt += right->Traverse(func);
        if( (this->*func)() ) {
            ++cnt;
        }
		return cnt;
	}

	int MaxDepth() const {
        int lc = 0, rc = 0;
		if( left ) lc = left->MaxDepth();
		if( right ) rc += right->MaxDepth();
		if( lc > rc ) return lc + 1;
        return rc + 1;
	}

    virtual bool isPlus() const { return false; }
    virtual bool isEq() const { return false; }
	virtual bool isIdent() const { return false; }
	virtual bool isVar() const { return false; }
	virtual string getId() const { return ""; }

    void CheckAssignments(map<string,bool>& var) {
		if( left ) left->CheckAssignments(var);
		if( right ) right->CheckAssignments(var);
        this->CheckAssign(var);
    }
        
	virtual void CheckAssign(map<string,bool>& var) {
		return;
	}
};

class StmtList : public Pt {

public:
	StmtList(Pt *l, Pt *r) : Pt(0, l, r) {}
};

class Print : public Pt {
public:
	Print(int line, Pt *e) : Pt(line, e) {}
};

class Println : public Pt {
public:
	Println(int line, Pt *e) : Pt(line, e) {}
};

class Repeat : public Pt {
public:
	Repeat(int line, Pt *e, Pt *s) : Pt(line, e, s) {}
};

class Assign : public Pt {
    string id;
public:
	Assign(int line, string id, Pt *l) : Pt(line,l), id(id) {}
    
    bool isEq() const { return true; }
    
	virtual void CheckAssign(map<string,bool>& var) {
		right->CheckAssign(var);
		var[ this->id ] = true;
	}
};

class PlusExpr : public Pt {
public:
	PlusExpr(int line, Pt *l, Pt *r) : Pt(line,l,r) {}
    bool isPlus() const { return true; }
};

class MinusExpr : public Pt {
public:
	MinusExpr(int line, Pt *l, Pt *r) : Pt(line,l,r) {}
};

class TimesExpr : public Pt {
public:
	TimesExpr(int line, Pt *l, Pt *r) : Pt(line,l,r) {}
};

class DivideExpr : public Pt {
public:
	DivideExpr(int line, Pt *l, Pt *r) : Pt(line,l,r) {}
};

class IConst : public Pt {
	int val;

public:
	IConst(Tok& t) : Pt(t.GetLinenum()) {
		val = stoi(t.GetLexeme());
	}
};

class SConst : public Pt {
	string val;

public:
	SConst(Tok& t) : Pt(t.GetLinenum()) {
		val = t.GetLexeme();
	}
};

class Ident : public Pt {
	string id;

public:
	Ident(Tok& t) : Pt(t.GetLinenum()), id(t.GetLexeme()) {}

	bool isIdent() const { return true; }
	string getId() const { return id; }
	virtual void CheckAssign(map<string,bool>& var) {
        if( var.find(getId()) == var.end() )
            std::cout << "UNDECLARED VARIABLE " << getId() << std::endl;
    }
};

#endif /* PT_H_ */
