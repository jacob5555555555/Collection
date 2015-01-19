#ifndef OBJECT_H
#define OBJECT_H

#include <cstddef> //size_t
#include <LazyCopyRef.h>
#include <string>

class Object;

typedef size_t Hash;
typedef LazyCopyRef<Object> ObjRef;

class Object
{
    public:
        Object();
        Hash hash() const;
        virtual std::string toString() const = 0;
        virtual bool operator==(const Object& other) const = 0;
        bool operator!=(const Object& other) const;
        virtual ObjRef get(ObjRef key) const = 0;
        virtual ~Object();
    protected:
        Hash mHash;
    private:
};

namespace std{
template<>
struct hash<Object>{
    size_t operator()(const Object& k) const{
        return k.hash();
    }
};
}

#endif // OBJECT_H
