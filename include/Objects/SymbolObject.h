#ifndef SYMBOLOBJECT_H
#define SYMBOLOBJECT_H

#include "Objects/Object.h"

#include <string>

class SymbolObject : public Object
{
    public:
        SymbolObject(const std::string& text);
        virtual bool compare(const Object& other) const;
        virtual ObjRef get(ObjRef key);
        virtual std::string toString() const;
        virtual ~SymbolObject();
    protected:
    private:
        std::string mText;
};

#endif // SYMBOLOBJECT_H
