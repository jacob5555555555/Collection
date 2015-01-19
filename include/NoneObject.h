#ifndef NONEOBJECT_H
#define NONEOBJECT_H

#include <Object.h>


class NoneObject : public Object
{
    public:
        NoneObject();
        virtual std::string toString() const;
        virtual bool operator==(const Object& other) const;
        virtual ObjRef get(ObjRef key) const;
        virtual ~NoneObject();
    protected:
    private:
};

#endif // NONEOBJECT_H
