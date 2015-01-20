#ifndef STATEMENT_H
#define STATEMENT_H

#include<vector>
#include<Object.h>

class Expression
{
    public:
        Expression(std::vector<ObjRef>&& objects);
        ObjRef evaluate();
        ~Expression();
    private:
        std::vector<ObjRef> objList;
};

#endif // STATEMENT_H
