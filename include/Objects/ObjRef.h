#ifndef OBJREF_H
#define OBJREF_H

#include <utility>
#include <functional>

#include "Hash.h"

class Object;

class ObjRef
{
public:
    ObjRef(Object* pointer);
    //copy constructors
    ObjRef(ObjRef& other);
    ObjRef(const ObjRef& other);
    ObjRef(ObjRef&& other);
    ObjRef(const ObjRef&& other);
    //assignment
    ObjRef& operator=(ObjRef other);
    //comparison
    bool operator==(const ObjRef& other) const;
    bool operator!=(const ObjRef& other) const;
    //destructor
    ~ObjRef();
    //get read-only reference to data
    const Object& getRO() const;
    Object* operator->() const;

    //swaps with another ObjRef<T>
    void swap(ObjRef other);
    Hash hash() const;

    //
    bool isNull();
private:
    Object* ptr;
};

namespace std{
template<>
struct hash<ObjRef>{
    size_t operator()(const ObjRef& ref) const{
        return ref.hash();
    }
};
}

#endif // OBJREF_H
