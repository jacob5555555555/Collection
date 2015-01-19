#ifndef USER_DEFINED_OBJECT_H
#define USER_DEFINED_OBJECT_H

#include <vector>
#include <LazyCopyRef.h>
#include <unordered_map>
#include <Object.h>

class UserDefinedObject;

class UserDefinedObject : Object
{
    public:
        UserDefinedObject();
        virtual ~UserDefinedObject();
        virtual Hash hash() const;
        virtual bool operator==(const Object& other) const;
        virtual std::string toString() const;
        virtual ObjRef get(ObjRef key) const;
        virtual void add(ObjRef key, ObjRef val);
    protected:
        std::unordered_map<ObjRef, ObjRef> objects;
    private:
};

Hash orderedHash(Hash a, Hash b);
inline Hash unorderedHash(Hash a, Hash b);

#endif // USER_DEFINED_OBJECT_H
