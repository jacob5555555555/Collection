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

UserDefinedObject::UserDefinedObject(){
}

UserDefinedObject::~UserDefinedObject(){
}

#define EMPTY_OBJECT_HASH 0xA987CC0
Hash UserDefinedObject::hash() const{
    std::hash<ObjRef> hasher;
    Hash hashSoFar = EMPTY_OBJECT_HASH;
    for (const auto& obj : objects){
        hashSoFar = unorderedHash(hashSoFar, orderedHash(hasher(obj.first), hasher(obj.second)));
    }
    return hashSoFar;
}

bool UserDefinedObject::operator==(const Object& other) const{
    const UserDefinedObject* usDefOther = dynamic_cast<const UserDefinedObject*>(&other);
    if(usDefOther == nullptr){
        return false;
    }else{
        return objects == usDefOther->objects;
    }
}

std::string UserDefinedObject::toString() const{
    string ret = "{";
    for (const auto& obj : objects){
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
    return objects.at(key);
}
void UserDefinedObject::add(ObjRef key, ObjRef val){
    objects.insert(make_pair(key, val));
}
