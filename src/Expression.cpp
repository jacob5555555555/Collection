#include "Expression.h"

using namespace std;

Expression::Expression(std::vector<ObjRef>&& objects):
    objList(objects)
{
    std::hash<ObjRef> hasher;
    Hash hashSoFar = 0;
    for (const auto& obj : objList){
        hashSoFar = orderedHash(hashSoFar, hasher(obj));
    }
    mHash = hashSoFar;

}

Expression::Expression(std::vector<ObjRef>& objects):
    objList(objects)
{
    std::hash<ObjRef> hasher;
    Hash hashSoFar = 0;
    for (const auto& obj : objList){
        hashSoFar = orderedHash(hashSoFar, hasher(obj));
    }
    mHash = hashSoFar;

}

Expression::~Expression()
{
}

ObjRef Expression::evaluate() const{
    ObjRef soFar = objList[0];
    for (size_t i = 1; i < objList.size(); ++i){
        soFar = soFar->get(objList[i]);
    }
    return soFar;
}

bool Expression::compare(const Object& other) const{
    const Expression* expOther = dynamic_cast<const Expression*>(&other);
    if(expOther == nullptr){
        return false;
    }else{
        return objList == expOther->objList;
    }
}

ObjRef Expression::get(ObjRef key) const{
    return evaluate()->get(key);
}

std::string Expression::toString() const{
    string ret = "(";
    for (const auto& obj : objList){
        ret += obj->toString();
        ret += ", ";
    }
    if (ret.size() >= 2){
        ret.pop_back();
        ret.pop_back();
    }
    ret += ")";
    return ret;
}

