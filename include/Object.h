#ifndef OBJECT_H
#define OBJECT_H

#include <vector>
#include <memory>

class Object
{
    public:
        Object();
        virtual ~Object();
    protected:
    private:
        std::vector<std::shared_ptr<Object>> objects;
        int hash;

};

template <typename T>
class BuiltinObject<T> : public Object{

};

#endif // OBJECT_H
