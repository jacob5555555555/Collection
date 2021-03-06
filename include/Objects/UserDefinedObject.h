#ifndef USER_DEFINED_OBJECT_H
#define USER_DEFINED_OBJECT_H

#include <vector>
#include <unordered_map>

#include "Objects/Object.h"

class UserDefinedObject;

class UserDefinedObject : public Object
{
    public:
        UserDefinedObject(std::unordered_map<ObjRef, ObjRef> objects);
        virtual ~UserDefinedObject();
        virtual bool compare(const Object& other) const;
        virtual std::string toString() const;
        virtual ObjRef get(ObjRef key);
    protected:
        std::unordered_map<ObjRef, ObjRef> mObjects;
    private:
};

#endif // USER_DEFINED_OBJECT_H
