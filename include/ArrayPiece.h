#ifndef ARRAYPIECE_H
#define ARRAYPIECE_H

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
        T get(int index){
            return getArray()[index];
        }
        int size(){
            return getHead()->used;
        }
        ~ArrayPiece() {
            free(data);
        }
    private:
        Head* getHead(){
            return (Head*) data;
        }
        T* getArray(){
            return (T*)(data + sizeof(Head)); //cast to char does nothing but stops warning message
        }
        struct Head{
            int used;
            int total;
        };
        DataPointer data = nullptr;
};

#endif // ARRAYPIECE_H
