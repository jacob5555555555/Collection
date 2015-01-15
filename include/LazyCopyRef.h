#ifndef LAZYCOPYREF_H
#define LAZYCOPYREF_H

template<typename T>
class LazyCopyRef
{
    public:
        template <typename ...Args>
        LazyCopyRef(Args&& ...params){
            data = new ValAndCount(params...);
        }
        LazyCopyRef(LazyCopyRef<T> &other){
            data = other.data;
            ++data->count;
        }
        ~LazyCopyRef(){
            --data->count;
            if (data->count == 0){
                delete data;
            }
        }
        T* get(){
            return &(data->val);
        }
    private:
        struct ValAndCount{
            template <typename ...Args>
            ValAndCount(Args&& ...params):
                    val(params...)
            {}
            T val;
            int count;
        };
        ValAndCount *data;
};

#endif // LAZYCOPYREF_H
