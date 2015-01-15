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
        virtual std::string toString() const;
        virtual ObjRef get(ObjRef key);
        virtual void add(ObjRef key, ObjRef val);
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

Hash orderedHash(Hash a, Hash b);
inline Hash unorderedHash(Hash a, Hash b);

#endif // OBJECT_H
