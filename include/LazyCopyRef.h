#ifndef LAZYCOPYREF_H
#define LAZYCOPYREF_H

#include <utility>
#include <iostream>
#include <memory>

template<typename T>
class LazyCopyRef{
public:
    LazyCopyRef(T* pointer): ptr(pointer){
    }
    //copy constructors
    LazyCopyRef(LazyCopyRef<T>& other): ptr(other.ptr){
    }
    LazyCopyRef(const LazyCopyRef<T>& other): ptr(other.ptr){
    }
    LazyCopyRef(LazyCopyRef<T>&& other): ptr(nullptr){
        swap(other);
    }
    LazyCopyRef(const LazyCopyRef<T>&& other): ptr(nullptr){
        swap(other);
    }
    //assignment
    LazyCopyRef<T> operator=(LazyCopyRef<T> other){
        swap(other);
    }
    //comparison
    bool operator==(const LazyCopyRef<T>& other) const{
        return *ptr == *(other.ptr);
    }
    //destructor
    ~LazyCopyRef(){
    }
    //get read-only reference to data
    const T& getRO() const{
        return *ptr;
    }

    //makes copy of data if this isn't the only LazyCopyRef<T> pointing to it, then returns reference
    T& get(){
        if(!ptr.unique()){
            deepCopy();
        }
        return *ptr;
    }
    //swaps with another LazyCopyRef<T>
    void swap(LazyCopyRef<T> other){
        ptr.swap(other.ptr);
    }
private:
    void deepCopy(){
        ptr.reset(new T(*ptr));
    }
    std::shared_ptr<T> ptr;
};

namespace std{
template<typename T>
struct hash<LazyCopyRef<T>>{
    size_t operator()(const LazyCopyRef<T>& ref) const{
        return std::hash<T>()(ref.getRO());
    }
};
}

#endif // LAZYCOPYREF_H
