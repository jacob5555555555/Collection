#include "FunctorObject.h"

using namespace std;

FunctorObject::FunctorObject(ObjRef(*func)(ObjRef obj)):
    mFunc(func)
{
    //ctor
}

FunctorObject::~FunctorObject()
{
    //dtor
}

bool FunctorObject::compare(const Object& other) const{
    const FunctorObject* funcOther = dynamic_cast<const FunctorObject*>(&other);
    if(funcOther == nullptr){
        return false;
    }else{
        return mFunc != funcOther->mFunc; //TODO
    }

}
string FunctorObject::toString() const{
    return "functor";
}

ObjRef FunctorObject::get(ObjRef key) const{
    return mFunc(key);
}
