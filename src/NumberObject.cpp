#include "NumberObject.h"

#include <Object.h>
#include <NoneObject.h>
#include <SymbolObject.h>
#include <FunctorObject.h>

using namespace std;

NumberObject::NumberObject(double num):
    mNum(num)
{
    mHash = std::hash<double>()(mNum);
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

ObjRef add (const NumberObject&  master, const NumberObject& key){
    return ObjRef(new NumberObject(master.mNum + key.mNum));
}
ObjRef subtract (const NumberObject&  master, const NumberObject& key){
    return ObjRef(new NumberObject(master.mNum - key.mNum));
}
ObjRef multiply (const NumberObject&  master, const NumberObject& key){
    return ObjRef(new NumberObject(master.mNum * key.mNum));
}
ObjRef divide (const NumberObject&  master, const NumberObject& key){
    return ObjRef(new NumberObject(master.mNum / key.mNum));
}

ObjRef NumberObject::get(ObjRef key) const{
    if (key == plusSym){
        return ObjRef(new FunctorObject<NumberObject, add>(*this));
    } else if (key == minusSym){
        return ObjRef(new FunctorObject<NumberObject, subtract>(*this));
    } else if (key == timesSym){
        return ObjRef(new FunctorObject<NumberObject, multiply>(*this));
    } else if (key == divideSym){
        return ObjRef(new FunctorObject<NumberObject, divide>(*this));
    } else {
        return ObjRef(new NoneObject);
    }
}
