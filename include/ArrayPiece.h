#ifndef ARRAYPIECE_H
#define ARRAYPIECE_H

#include <string.h>//memmove

const static int EXTRA = 4;
typedef char* DataPointer; //char* and not void* to avoid warnings

template <typename T>
class ArrayPiece
{
    struct Head;
    public:
        ArrayPiece(int size) {
            int total = size + EXTRA;
            data = (DataPointer)malloc(sizeof(Head) + sizeof(T) * (total));
            getHead()->used = 0;
            getHead()->total = total;
        }
        bool isComplete(){
            return getHead()->used >= getHead()->total - EXTRA;
        }
        bool canAdd(){
            return getHead()->used == getHead()->total;
        }
        void add(T val){
            getArray()[getHead()->used] = val;
            ++getHead()->used;
        }
        void replace(T val, int index){
            getArray()[index] = val;
        }
        T get(int index){
            return getArray()[index];
        }
        int size(){
            return getHead()->used;
        }
        void insert(T val, int index){
            memmove(getArray()+index+1, getArray()+index, sizeof(T) * (size() - index));
            replace(val, index);
            ++getHead()->used;
        }
        ArrayPiece<T> subArray(int start, size_t size){
            ArrayPiece<T> newArr(size);
            memcpy(newArr.getArray(),getArray()+start, size * sizeof(T));
            newArr.getHead()->used = size;
            return newArr;
        }
        ~ArrayPiece() {
            free(data);
        }
    private:
        Head* getHead(){
            return (Head*) data;
        }
        T* getArray(){
            return (T*)(data + sizeof(Head));
        }
        struct Head{
            int used;
            int total;
        };
        DataPointer data = nullptr;
};

#endif // ARRAYPIECE_H
