#include "NoneObject.h"
#include <type_traits>

using namespace std;

NoneObject::NoneObject()
{
    //ctor
}

string NoneObject::toString() const{
    return "None";
}
bool NoneObject::operator==(const Object& other) const{
    if(hash() != other.hash()){
        return false;
    } else if(typeid(this) != typeid(other)){
        return false;
    } else {
        return true;
    }
}
ObjRef NoneObject::get(ObjRef key) const{
    return ObjRef(new NoneObject);
}


NoneObject::~NoneObject()
{
    //dtor
}
