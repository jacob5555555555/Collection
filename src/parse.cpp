#include "parse.h"

#include <iostream>
#include <algorithm>

#include "Objects/Expression.h"
#include "Objects/NumberObject.h"
#include "Objects/UserDefinedObject.h"
#include "Objects/SymbolObject.h"
#include "Objects/NoneObject.h"

using namespace std;

namespace{
    ObjRef asNum(string str){
        char *strEnd = &str.back();
        double value = strtod(&str.front(), &strEnd);
        if (strEnd == &str.front()){
            return ObjRef(nullptr);
        }else{
            return ObjRef(new NumberObject(value));
        }
    }

    ObjRef asSymbol(string str){
        return ObjRef(new SymbolObject(str));
    }
}

ObjRef parse(std::vector<std::string>::iterator begin, std::vector<std::string>::iterator end){
    vector<ObjRef> objl;
    while (begin != end){
        ObjRef next(nullptr);
        if (*begin == "("){
            int depth = 1;
            vector<string>::iterator subExpEnd = begin;
            while(depth != 0){
                ++subExpEnd;
                if (subExpEnd == end){
                    return ObjRef(new NoneObject); //error, mismatch parenthases
                }
                if (*subExpEnd == "("){
                    ++depth;
                } else if (*subExpEnd == ")"){
                    --depth;
                }
            }
            //from after "(" tp ")"
            objl.push_back(parse(begin + 1, subExpEnd));
            begin = subExpEnd + 1;
        } else {
            ObjRef next(nullptr);
            next = asNum(*begin);
            if (next == ObjRef(nullptr)){
                next = asSymbol(*begin);
            }
            objl.push_back(next);
            ++begin;
        }
    }
    return ObjRef(new Expression(objl));
}

ObjRef parseString(std::string str){
    size_t start = 0, next = 0;
    vector<string> strs;
    //find next word
    while (next != str.size()){
        while (start != str.size() && isspace(str[start])){
            start += 1;
        }
        next = start;
        //find end of word
        while (next != str.size() && !isspace(str[next])){
            next += 1;
        }
        strs.push_back(str.substr(start, next - start));
        start = next;
    }
    vector<string>::iterator begin = strs.begin();
    vector<string>::iterator end = strs.end();
    return parse(begin, end);
}
