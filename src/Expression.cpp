#include "Expression.h"

Expression::Expression(std::vector<ObjRef>&& objects):
    objList(objects)
{
}

Expression::~Expression()
{
}

ObjRef Expression::evaluate(){
    ObjRef soFar = objList[0];
    for (size_t i = 1; i < objList.size(); ++i){
        soFar = soFar->get(objList[i]);
    }
    return soFar;
}
