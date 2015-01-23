#ifndef NONEOBJECT_H
#define NONEOBJECT_H

#include "Objects/Object.h"


class NoneObject : public Object
{
    public:
        NoneObject();
        virtual std::string toString() const;
        virtual bool compare(const Object& other) const;
        virtual ObjRef get(ObjRef key);
        virtual ~NoneObject();
    protected:
    private:
};

#endif // NONEOBJECT_H
