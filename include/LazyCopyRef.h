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
        LazyCopyRef(LazyCopyRef<T>& other): data(other.data){
            data->count += 1;
        }
        LazyCopyRef(LazyCopyRef<T>&& other): data(nullptr){
            swap(other);
        }
        LazyCopyRef<T> operator=(LazyCopyRef<T> other){
            swap(other);
        }
        ~LazyCopyRef(){
            data->count -= 1;
            if (data != nullptr && data->count == 0){
                delete data;
            }
        }
        const T& getRO(){
            return data->val;
        }
        T& get(){
            if(data->count != 1){
                deepCopy();
            }
            return data->val;
        }
        void deepCopy(){
            if(data->count != 1){
                data->count -= 1;
                T& oldVal = data->val;
                data = new ValAndCount(oldVal);
                data->count = 1;
            }
        }
        void swap(LazyCopyRef<T> other){
            std::swap(data, other.data);
        }
    private:
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
