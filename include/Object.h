#ifndef OBJECT_H
#define OBJECT_H

#include <vector>
#include <LazyCopyRef.h>
#include <unordered_map>

class Object;

typedef size_t Hash;

typedef LazyCopyRef<Object> ObjRef;

class Object
{
    public:
        Object();
        virtual ~Object();
        virtual Hash hash() const;
        virtual bool operator==(const Object& other) const;
    protected:
        std::unordered_map<ObjRef, ObjRef> objects;
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
