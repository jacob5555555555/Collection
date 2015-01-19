#include "Object.h"

Object::Object()
{
}

Hash Object::hash() const{
    return mHash;
}

bool Object::operator!=(const Object& other) const{
    return !operator==(other);
}

Object::~Object()
{
}
