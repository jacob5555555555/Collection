#include "UserDefinedObject.h"
#include <Object.h>

using namespace std;

#define EMPTY_OBJECT_HASH 0xAC975FF0

UserDefinedObject::UserDefinedObject(std::unordered_map<ObjRef, ObjRef> objects):
    mObjects(objects)
{
    std::hash<ObjRef> hasher;
    Hash hashSoFar = EMPTY_OBJECT_HASH;
    for (const auto& obj : mObjects){
        hashSoFar = unorderedHash(hashSoFar, orderedHash(hasher(obj.first), hasher(obj.second)));
    }
    mHash = hashSoFar;

}

UserDefinedObject::~UserDefinedObject(){
}

bool UserDefinedObject::compare(const Object& other) const{
    const UserDefinedObject* usDefOther = dynamic_cast<const UserDefinedObject*>(&other);
    if(usDefOther == nullptr){
        return false;
    }else{
        return mObjects == usDefOther->mObjects;
    }
}

std::string UserDefinedObject::toString() const{
    string ret = "{";
    for (const auto& obj : mObjects){
        ret += obj.first.getRO().toString();
        ret += ": ";
        ret += obj.second.getRO().toString();
        ret += ", ";
    }
    ret.pop_back();
    ret.pop_back();//remove last ", "
    ret += "}";
    return ret;
}
ObjRef UserDefinedObject::get(ObjRef key) const{
    return mObjects.at(key);
}
