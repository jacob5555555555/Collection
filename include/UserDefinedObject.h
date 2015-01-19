#ifndef USER_DEFINED_OBJECT_H
#define USER_DEFINED_OBJECT_H

#include <vector>
#include <LazyCopyRef.h>
#include <unordered_map>
#include <Object.h>

class UserDefinedObject;

class UserDefinedObject : public Object
{
    public:
        UserDefinedObject(std::unordered_map<ObjRef, ObjRef> objects);
        virtual ~UserDefinedObject();
        virtual bool compare(const Object& other) const;
        virtual std::string toString() const;
        virtual ObjRef get(ObjRef key) const;
    protected:
        std::unordered_map<ObjRef, ObjRef> mObjects;
    private:
};

Hash orderedHash(Hash a, Hash b);
inline Hash unorderedHash(Hash a, Hash b);

#endif // USER_DEFINED_OBJECT_H
