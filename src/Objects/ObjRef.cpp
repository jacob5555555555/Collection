#include "Objects/ObjRef.h"

#include <utility>
#include <iostream>

#include "Objects/Object.h"

using namespace std;

ObjRef::ObjRef(Object* pointer): ptr(pointer){
    if (ptr != nullptr)
        ptr -> _refCount += 1;
}

//copy constructors
ObjRef::ObjRef(ObjRef& other): ptr(other.ptr){
    if (ptr != nullptr)
        ptr-> _refCount += 1;
}
ObjRef::ObjRef(const ObjRef& other): ptr(other.ptr){
    if (ptr != nullptr)
        ptr -> _refCount += 1;
}
ObjRef::ObjRef(ObjRef&& other): ptr(nullptr){
    swap(other);
}
ObjRef::ObjRef(const ObjRef&& other): ptr(nullptr){
    swap(other);
}
//assignment
ObjRef& ObjRef::operator=(ObjRef other){ //TODO should initialize to nullptr?
    swap(other);
    return *this;
}

//assignment
bool ObjRef::operator==(const ObjRef& other) const{
    if (ptr == other.ptr){
        return true;
    }
    if (ptr == nullptr || other.ptr == nullptr){
        return false;
    }
    return *ptr == *(other.ptr);
}
bool ObjRef::operator!=(const ObjRef& other) const{
    return !operator==(other);
}

//get a read only reference
const Object& ObjRef::getRO() const{
    return *ptr;
}

//swaps with another ObjRef<T>
void ObjRef::swap(ObjRef other){
    std::swap(ptr, other.ptr);
}

Object* ObjRef::operator->() const{
    return ptr;
}

Hash ObjRef::hash() const{
    return ptr->hash();
}

ObjRef::~ObjRef()
{
    if (ptr != nullptr){
        ptr->_refCount -= 1;
        if (ptr -> _refCount == 0){
            delete ptr;
        }
    }
}
