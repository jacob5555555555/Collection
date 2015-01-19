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

        friend ObjRef add(const NumberObject&  master, const NumberObject& key);
        friend ObjRef subtract(const NumberObject&  master, const NumberObject& key);
        friend ObjRef multiply(const NumberObject&  master, const NumberObject& key);
        friend ObjRef divide(const NumberObject&  master, const NumberObject& key);
};

#endif // NUMBEROBJECT_H
