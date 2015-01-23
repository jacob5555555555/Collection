#include "Object.h"
#include <NumberObject.h>
#include <ObjRef.h>

Hash orderedHash(Hash a, Hash b){
    return b ^ (b >> (a % 4));
}

Hash unorderedHash(Hash a, Hash b){
    return a ^ b;
}

static inline Hash removeUnorderedHash(Hash keep, Hash remove){
    return keep ^ remove;
}

Object::Object():
    _refCount(0)
{
}

Hash Object::hash() const{
    return mHash;
}

bool Object::operator==(const Object& other) const{
    if (hash() != other.hash()){
        return false;
    } else {
        return compare(other);
    }
}

bool Object::operator!=(const Object& other) const{
    return !operator==(other);
}

ObjRef Object::evaluate(){
    return ObjRef(this);
}

Object::~Object()
{
}
