#include "UserDefinedObject.h"

using namespace std;

Hash orderedHash(Hash a, Hash b){
    return b ^ (b >> (a % 4));
}

inline Hash unorderedHash(Hash a, Hash b){
    return a ^ b;
}

static inline Hash removeUnorderedHash(Hash keep, Hash remove){
    return keep ^ remove;
}

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

bool UserDefinedObject::operator==(const Object& other) const{
    if (hash() != other.hash()){
        return false;
    }
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
