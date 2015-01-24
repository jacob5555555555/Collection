#ifndef TOKENIZER_H
#define TOKENIZER_H

#include <unordered_map>
#include <istream>
#include <iterator>
#include <string>

#include "Objects/Object.h"
#include "Objects/ObjRef.h"

class Tokenizer
{
    public:
        Tokenizer(std::istream& in);
        ObjRef next();
        bool eof();
        ~Tokenizer();
    private:
        std::string nextWord();

        std::istream_iterator<char> inIter;
};

#endif // TOKENIZER_H
