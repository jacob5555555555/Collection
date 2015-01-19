#include "NoneObject.h"
#include <type_traits>

using namespace std;

NoneObject::NoneObject()
{
    mHash = 0;
}

string NoneObject::toString() const{
    return "None";
}
bool NoneObject::operator==(const Object& other) const{
    if(hash() != other.hash()){
        return false;
    }
    const NoneObject* noneOther = dynamic_cast<const NoneObject*>(&other);
    if(noneOther == nullptr){
        return false;
    }else{
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
