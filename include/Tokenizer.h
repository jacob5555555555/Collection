#ifndef TOKENIZER_H
#define TOKENIZER_H

#include<unordered_map>
#include<istream>
#include <string>

enum TokenType{
    //control tokens
    END,
    INVALID,
    //literals
    NUMBER,
    CHARACTER,
    BOOLEAN,
    //keywords
    IF,
    ELSE
};

struct Token{
    TokenType type;
    union {

        double number;
        char character;
        bool boolean;
    }value;
    std::string error;
};

class Tokenizer
{
    public:
        Tokenizer(std::istream &in);
        void next(Token &out);
        ~Tokenizer();
    private:
        std::istream &instream;
};

#endif // TOKENIZER_H
