#include "Parsing/Tokenizer.h"

#include <iostream>
#include <string>

#include "Objects/NumberObject.h"
#include "Objects/SymbolObject.h"

using namespace std;

Tokenizer::Tokenizer(std::istream &in):
    inIter(in)
{
}

Tokenizer::~Tokenizer()
{
    //dtor
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

ObjRef Tokenizer::next(){
    string word = nextWord();
    ObjRef ret = asNum(word);
    if (ret.isNull()){
        ret = asSymbol(word);
    }
    return ret;
}

const istream_iterator<char> EOS;
bool Tokenizer::eof(){
    return inIter == EOS;
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

#include <iostream>

std::string Tokenizer::nextWord(){
    string word;
    word += *inIter++;
    while(!eof() && !isEndChar(*inIter)){
        word += (*inIter);
        ++inIter;
    }
    return word;
}
