#ifndef OBJECT_H
#define OBJECT_H

#include <vector>
#include <LazyCopyRef.h>
#include <unordered_set>

typedef size_t Hash;

class Object;


class Object
{
    public:
        Object();
        virtual ~Object();
        virtual Hash hash() const;
    protected:
    private:
        std::unordered_set<LazyCopyRef<Object>> objects;
        Hash mHash;

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
