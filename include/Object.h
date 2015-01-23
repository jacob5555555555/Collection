#ifndef OBJECT_H
#define OBJECT_H

#include <cstddef> //size_t
#include <string>

#include "ObjRef.h"
#include "Hash.h"

class Object;

class Object
{
    friend class ObjRef;
    public:
        Object();
        Hash hash() const;
        virtual std::string toString() const = 0;
        bool operator==(const Object& other) const;
        virtual bool compare(const Object& other) const = 0;
        bool operator!=(const Object& other) const;
        virtual ObjRef evaluate();
        virtual ObjRef get(ObjRef key) = 0;
        virtual ~Object();
    protected:
        Hash mHash;
    private:
        int _refCount;
};

namespace std{
template<>
struct hash<Object>{
    size_t operator()(const Object& k) const{
        return k.hash();
    }
};
}

Hash orderedHash(Hash a, Hash b);
Hash unorderedHash(Hash a, Hash b);

#endif // OBJECT_H
