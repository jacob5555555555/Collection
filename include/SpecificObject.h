#ifndef SPECIFICOBJECT_H
#define SPECIFICOBJECT_H

#include <Object.h>
#include <sstream>
#include <typeinfo>

template<typename T>
class SpecificObject : public Object
{
    public:
        SpecificObject(T val): mVal(val){
        }
        virtual ~SpecificObject(){}
        virtual Hash hash() const{
            return orderedHash(std::hash<T>()(mVal), Object::hash());
        }
        virtual std::string toString() const{
            std::string ret;
            std::stringstream ss;
            ss << mVal;
            ss >> ret;
            return ret;
        }
    virtual bool operator==(const Object& other) const{
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
