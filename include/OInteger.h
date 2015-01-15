#ifndef OINTEGER_H
#define OINTEGER_H

typedef long long Integer;

class OInteger : public Object
{
    public:
        OInteger();
        virtual ~OInteger();
    protected:
        Integer val;
    private:
};

#endif // OINTEGER_H
