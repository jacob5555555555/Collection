#include "NumberObject.h"

#include <NoneObject.h>
#include <SymbolObject.h>

using namespace std;

NumberObject::NumberObject(double num):
    mNum(num)
{
}

NumberObject::~NumberObject()
{
    //dtor
}

bool NumberObject::compare(const Object& other) const{
    const NumberObject* numOther = dynamic_cast<const NumberObject*>(&other);
    if(numOther == nullptr){
        return false;
    }else{
        return mNum == numOther->mNum;
    }

}
string NumberObject::toString() const{
    return to_string(mNum);
}

const ObjRef plusSym(new SymbolObject("+"));
const ObjRef minusSym(new SymbolObject("-"));
const ObjRef timesSym(new SymbolObject("*"));
const ObjRef divideSym(new SymbolObject("/"));

ObjRef NumberObject::get(ObjRef key) const{
    if (key == plusSym){

    } else if (key == minusSym){

    } else if (key == timesSym){

    } else if (key == divideSym){

    } else {
        return ObjRef(new NoneObject);
    }
}
