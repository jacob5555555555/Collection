#ifndef SPECIFICOBJECT_H
#define SPECIFICOBJECT_H

#include <Object.h>
#include <sstream>

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
    protected:
        T mVal;
    private:
};

#endif // SPECIFICOBJECT_H
