#ifndef FUNCTOROBJECT_H
#define FUNCTOROBJECT_H

#include <Object.h>
#include <NoneObject.h>

class FunctorObject : public Object
{
    public:
        FunctorObject(ObjRef(*func)(ObjRef obj));
        virtual ~FunctorObject();
        virtual bool compare(const Object& other) const;
        virtual ObjRef get(ObjRef key) const;
        virtual std::string toString() const;

    protected:
    private:
        ObjRef(*mFunc)(ObjRef obj);
};

};

#endif // FUNCTOROBJECT_H
