#ifndef SPECIFICOBJECT_H
#define SPECIFICOBJECT_H

#include <sstream>
#include <typeinfo>

#include "Objects/Object.h"
#include "Objects/NoneObject.h"

template<typename T>
class SpecificObject : public Object
{
    public:
        SpecificObject(T val): mVal(val){
            mHash = std::hash<T>()(val);
        }
        virtual ~SpecificObject(){}
        virtual std::string toString() const{
            std::string ret;
            std::stringstream ss;
            ss << mVal;
            ss >> ret;
            return ret;
        }
    virtual ObjRef get(ObjRef key){
        return ObjRef(new NoneObject);
    }
    virtual bool compare(const Object& other) const{
        const SpecificObject<T>* specOther = dynamic_cast<const SpecificObject<T>*>(&other);
        if(specOther == nullptr){
            return false;
        }else{
            return mVal == specOther->mVal;
        }
    }
    protected:
        T mVal;
    private:
};

#endif // SPECIFICOBJECT_H
