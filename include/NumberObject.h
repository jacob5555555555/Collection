#ifndef NUMBEROBJECT_H
#define NUMBEROBJECT_H

#include <Object.h>


class NumberObject : public Object
{
    public:
        NumberObject(double num);
        virtual ~NumberObject();
        virtual bool compare(const Object& other) const;
        virtual ObjRef get(ObjRef key) const;
        virtual std::string toString() const;
    protected:
    private:
        double mNum;
};

#endif // NUMBEROBJECT_H
