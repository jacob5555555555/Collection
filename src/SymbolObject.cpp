#include "SymbolObject.h"
#include <NoneObject.h>

using namespace std;

SymbolObject::SymbolObject(const std::string& text)
{
    mHash = std::hash<string>()(text);
}

SymbolObject::~SymbolObject()
{
    //dtor
}

string SymbolObject::toString() const{
    return mText;
}

bool SymbolObject::compare(const Object& other) const{
    const SymbolObject* symOther = dynamic_cast<const SymbolObject*>(&other);
    if(symOther == nullptr){
        return false;
    }else{
        return mText == symOther->mText;
    }
}

ObjRef SymbolObject::get(ObjRef key) const{
    return ObjRef(new NoneObject);
}
