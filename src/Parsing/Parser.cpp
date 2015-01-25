#include "Parsing/Parser.h"

#include <string>
#include <vector>
#include <iostream>

#include "Objects/ObjRef.h"
#include "Objects/Expression.h"
#include "Objects/NumberObject.h"
#include "Objects/SymbolObject.h"

using namespace std;

Parser::Parser(std::istream &in):
    stream(in)
{
}

Parser::~Parser()
{
    //dtor
}

static bool isEndChar(char c){
    if (isspace(c)){
        return true;
    } else if (isdigit(c)){
        return true;
    }
    switch (c){
    case '-':
    case '+':
    case '*':
    case '/':
    case '?':
    case '^':
    case '(':
    case ')':
        return true;
    default: //if not a special character
        return false;
    }

}

std::string Parser::nextWord(){
    string word;
    int nextChar;

    do{
        nextChar = stream.get();
    }while(isspace(nextChar));

    word += nextChar;
    if (isEndChar(nextChar)){
        return word;
    }

    while(!isEndChar(nextChar)){
        nextChar = stream.get();
        word += nextChar;
    }
    return word;
}

bool Parser::eof(){
    return stream.eof();
}

/*static bool isChar(string &str, Token &token){
    if (str.size() != 3 || str[0] != '\'' || str[2] != '\'')
        return false;
    token.type = CHARACTER;
    token.value.character = str[1];
    return true;
}*/

static ObjRef asNum(string &str){
    char *strEnd = &str.back();
    double value = strtod(&str.front(), &strEnd);
    if (strEnd == &str.front()){
        return ObjRef(nullptr);
    }else{
        return ObjRef(new NumberObject(value));
    }
}

/*static bool isBool(string &str, Token &token){
    if(str == "True"){
        token.type = BOOLEAN;
        token.value.boolean = true;
        return true;
    }
    if(str == "False"){
        token.type = BOOLEAN;
        token.value.boolean = false;
        return true;
    }
    return false;
}*/

static ObjRef asSymbol(string& word){
    return ObjRef(new SymbolObject(word));
}

ObjRef Parser::next(string word){
    if (word == "("){
        return parse();
    }

    ObjRef ret = asNum(word);
    if (ret.isNull()){
        ret = asSymbol(word);
    }
    return ret;
}

ObjRef Parser::parse(){
    vector<ObjRef> objList;
    string word;
    while(!eof()){
        word = nextWord();
        if (word == ")"){
            break;
        }
        objList.push_back(next(word));
    }
    ObjRef express(new Expression(objList));
    return express;
}

