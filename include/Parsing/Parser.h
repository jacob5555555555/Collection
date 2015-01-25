#ifndef TOKENIZER_H
#define TOKENIZER_H

#include <unordered_map>
#include <istream>
#include <iterator>
#include <string>

#include "Objects/Object.h"
#include "Objects/ObjRef.h"

class Parser
{
public:
    Parser(std::istream& in);
    ObjRef parse();
    bool eof();
    ~Parser();
private:
    std::string nextWord();
    ObjRef next(std::string word);

    std::istream& stream;
};

#endif // TOKENIZER_H
