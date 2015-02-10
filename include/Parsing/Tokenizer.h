#ifndef TOKENIZER_H
#define TOKENIZER_H


class Tokenizer
{
    public:
        Tokenizer(std::istream& inStream);
        ~Tokenizer();
    private:
        std::istream& mStream;

        std::string nextToken();
};

#endif // TOKENIZER_H
