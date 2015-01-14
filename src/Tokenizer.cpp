#include "Tokenizer.h"
#include <iostream>
#include <string>

using namespace std;

Tokenizer::Tokenizer(std::istream &in):
    instream(in)
{
}

Tokenizer::~Tokenizer()
{
    //dtor
}

static bool isChar(string &str, Token &token){
    if (str.size() != 3 || str[0] != '\'' || str[2] != '\'')
        return false;
    token.type = CHARACTER;
    token.value.character = str[1];
    return true;
}

static bool isNum(string &str, Token &token){
    char *strEnd = &str.back();
    double value = strtod(&str.front(), &strEnd);
    if (strEnd == &str.front()){
        return false;
    }else{
        token.type = NUMBER;
        token.value.number = value;
        return true;
    }
}

static bool isBool(string &str, Token &token){
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
}

static bool isKeyWord(string &str, Token &token){
    if (str == "if"){
        token.type = IF;
        return true;
    }
    if (str == "else"){
        token.type = ELSE;
        return true;
    }
    return false;
}

void Tokenizer::next(Token &out){
    if (instream.eof()){
        out.type = END;
        return;
    }
    string text;
    instream >> text;

    if(!isChar(text, out)
        && !isNum(text, out)
        && !isBool(text, out)
        && !isKeyWord(text, out)){

        out.type = INVALID;
        out.error = string("`") + text + "' is not a valid token";
    }
}
