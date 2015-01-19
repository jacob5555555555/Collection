#ifndef FUNCTOROBJECT_H
#define FUNCTOROBJECT_H

#include <Object.h>
#include <NoneObject.h>

template <typename T, ObjRef func(const T& master, const T& key)> //where T is subclass of Object
class FunctorObject : public Object{
public:
    FunctorObject(const T& creator):master(creator)
    {}
    virtual ~FunctorObject(){}

    virtual bool compare(const Object& other) const{
        const FunctorObject<T, func>* funcOther = dynamic_cast<const FunctorObject<T, func>*>(&other);
        if(funcOther == nullptr){
            return false;
        }else{
            return true;
        }
    }

    virtual ObjRef get(ObjRef key) const{
        const T* tObj = dynamic_cast<const T*>(&key.getRO());
        if (tObj == nullptr){
            return ObjRef(new NoneObject);
        } else {
            return func(master, *tObj);
        }
    }

    virtual std::string toString() const{
        return "functor";
    }

    const T& master;
};

#endif // FUNCTOROBJECT_H
