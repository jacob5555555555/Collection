#ifndef STATEMENT_H
#define STATEMENT_H

#include<vector>
#include<Object.h>

class Expression : public Object
{
public:
    Expression(std::vector<ObjRef>&& objects);
    Expression(std::vector<ObjRef>& objects);
    ~Expression();
    virtual ObjRef evaluate();
    virtual bool compare(const Object& other) const;
    virtual ObjRef get(ObjRef key);
    virtual std::string toString() const;
private:
    std::vector<ObjRef> objList;
};

#endif // STATEMENT_H
