#include "NumberObject.h"

#include <NoneObject.h>
#include <SymbolObject.h>
#include <FunctorObject.h>

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

//TODO: make FunctorObject have func of type ObjRef(*)(ObjRef caller, ObjRef arg), where the FunctorObject class has a member ObjRef caller

ObjRef NumberObject::get(ObjRef key) const{

    double num = mNum;
    const ObjRef plusFunc(new FunctorObject( [num](ObjRef other)->ObjRef{
        const NumberObject* numOther = dynamic_cast<const NumberObject*>(&other.getRO());
        if(numOther == nullptr){
            return ObjRef(new NoneObject);
        }else{
            return ObjRef(new NumberObject(num + numOther->mNum));
        }
    }));

    const ObjRef minusFunc(new FunctorObject( [num](ObjRef other)->ObjRef{
        const NumberObject* numOther = dynamic_cast<const NumberObject*>(&other.getRO());
        if(numOther == nullptr){
            return ObjRef(new NoneObject);
        }else{
            return ObjRef(new NumberObject(num - numOther->mNum));
        }
    }));

    const ObjRef timesFunc(new FunctorObject( [num](ObjRef other)->ObjRef{
        const NumberObject* numOther = dynamic_cast<const NumberObject*>(&other.getRO());
        if(numOther == nullptr){
            return ObjRef(new NoneObject);
        }else{
            return ObjRef(new NumberObject(num * numOther->mNum));
        }
    }));

    const ObjRef divideFunc(new FunctorObject( [num](ObjRef other)->ObjRef{
        const NumberObject* numOther = dynamic_cast<const NumberObject*>(&other.getRO());
        if(numOther == nullptr){
            return ObjRef(new NoneObject);
        }else{
            return ObjRef(new NumberObject(num / numOther->mNum));
        }
    }));



    if (key == plusSym){
        return plusFunc;
    } else if (key == minusSym){
        return minusFunc;
    } else if (key == timesSym){
        return timesFunc;
    } else if (key == divideSym){
        return divideFunc;
    } else {
        return ObjRef(new NoneObject);
    }
}
