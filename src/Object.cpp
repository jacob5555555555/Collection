#include "Object.h"

using namespace std;

static Hash orderedHash(Hash a, Hash b){
    return b ^ (b >> (a % 4));
}

static inline Hash unorderedHash(Hash a, Hash b){
    return a ^ b;
}

static inline Hash removeUnorderedHash(Hash keep, Hash remove){
    return keep ^ remove;
}

Object::Object(){
}

Object::~Object(){
}

#define EMPTY_OBJECT_HASH 0xA987CC0
Hash Object::hash() const{
    std::hash<ObjRef> hasher;
    Hash hashSoFar = EMPTY_OBJECT_HASH;
    for (const auto& obj : objects){
        hashSoFar = unorderedHash(hashSoFar, orderedHash(hasher(obj.first), hasher(obj.second)));
    }
    return hashSoFar;
}

bool Object::operator==(const Object& other) const{
    /* //cant use now because hash recomputes every time
    if (hash() != other.hash()){
        return false;
    }
    */
    return objects == other.objects;
}
