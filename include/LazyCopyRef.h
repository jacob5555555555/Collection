#ifndef LAZYCOPYREF_H
#define LAZYCOPYREF_H

#include <utility>
#include <iostream>

template<typename T>
class LazyCopyRef
{
    public:
        template <typename ...Args>
        LazyCopyRef(Args&& ...params){
            data = new ValAndCount(params...);
            data->count = 1;
        }

        //copy constructors
        LazyCopyRef(LazyCopyRef<T>& other): data(other.data){
            data->count += 1;
        }
        LazyCopyRef(const LazyCopyRef<T>& other): data(other.data){
            data->count += 1;
        }
        LazyCopyRef(LazyCopyRef<T>&& other): data(nullptr){
            swap(other);
        }
        LazyCopyRef(const LazyCopyRef<T>&& other): data(nullptr){
            swap(other);
        }

        //assignment
        LazyCopyRef<T> operator=(LazyCopyRef<T> other){
            swap(other);
        }

        //comparison
        bool operator==(const LazyCopyRef<T>& other) const{
            return other.data->val == data->val;
        }

        //destructor
        ~LazyCopyRef(){
            data->count -= 1;
            if (data != nullptr && data->count == 0){
                delete data;
            }
        }

        //get read-only reference to data
        const T& getRO() const{
            return data->val;
        }

        //makes copy of data if this isn't the only LazyCopyRef<T> pointing to it, then returns reference
        T& get(){
            if(data->count != 1){
                deepCopy();
            }
            return data->val;
        }
        //swaps with another LazyCopyRef<T>
        void swap(LazyCopyRef<T> other){
            std::swap(data, other.data);
        }
    private:
        void deepCopy(){
            if(data->count != 1){
                data->count -= 1;
                T& oldVal = data->val;
                data = new ValAndCount(oldVal);
                data->count = 1;
            }
        }
        struct ValAndCount{
            template <typename ...Args>
            ValAndCount(Args&& ...params):
                    val(params...)
            {}
            ValAndCount(T& toCopy):
                val(toCopy)
            {}
            T val;
            int count;
        };
        ValAndCount *data;
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
