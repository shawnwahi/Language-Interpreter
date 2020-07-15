#include "val.h"

// add op to this
Value Value::operator+(const Value& op) const {
    if( GetType() != op.GetType() || IsErr() )
        throw string("Type error on addition");

    if( IsInt() ) return Value( I + op.GetInt() );
    return Value( S + op.GetStr() );
}
    
// subtract op from this
Value Value::operator-(const Value& op) const {
    if( GetType() != op.GetType() || IsErr() )
        throw string("Type error on subtraction");

    if( IsInt() ) return Value( I - op.GetInt() );
    // find the string op in this
    auto srch = S.find( op.GetStr() );

    string result = S;
    if( srch != string::npos )
        result.erase(srch, op.GetStr().length());
    return result;
}
    
// multiply this by op
Value Value::operator*(const Value& op) const {
    if( IsInt() && op.IsInt() )
        return Value( I * op.GetInt() );

    if( IsInt() && op.IsStr() ) {
        if( I < 0 )
            throw string("Multiply string by negative number");
        string result;
        result.reserve( I * op.GetStr().length() );
        for( int i=0; i<I; i++ )
            result += op.GetStr();
        return result;
    }
    else if( IsStr() && op.IsInt() ) {
        if( op.GetInt() < 0 )
            throw string("Multiply string by negative number");
        string result;
        result.reserve( op.GetInt() * S.length() );
        for( int i=0; i<op.GetInt(); i++ )
            result += S;
        return result;
    }
    throw string("Type error on multiplication");
}
    
// divide this by op
Value Value::operator/(const Value& op) const {
    if( !(IsInt() && op.IsInt()))
        throw string("Type error on division");

    if( op.GetInt() == 0 )
        throw string("Divide by zero");

    return Value( I / op.GetInt() );
}
