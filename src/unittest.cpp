#include <unittest++/UnitTest++.h>

#include <string>

#include "Tokenizer.h"
#include "Objects/SpecificObject.h"
#include "Objects/UserDefinedObject.h"
#include "Objects/SymbolObject.h"
#include "Objects/NumberObject.h"
#include "Objects/FunctorObject.h"
#include "Objects/NoneObject.h"
#include "Objects/Expression.h"
#include "parse.h"

using namespace std;

//tests
SUITE(Hashing){
    TEST(HashIsConsistent){
        ObjRef ref1(new UserDefinedObject(std::unordered_map<ObjRef, ObjRef>({
                                            {ObjRef(new SpecificObject<int>(143)), ObjRef(new SpecificObject<string>("beach"))},
                                            {ObjRef(new SpecificObject<float>(534.1)), ObjRef(new SpecificObject<long>(9876))}
                                          })));
        ObjRef ref2(new UserDefinedObject({
                                            {ObjRef(new SpecificObject<float>(534.1)), ObjRef(new SpecificObject<long>(9876))},
                                            {ObjRef(new SpecificObject<int>(143)), ObjRef(new SpecificObject<string>("beach"))}
                                          }));
        CHECK(ref1.getRO().hash() == ref2.getRO().hash());

        ObjRef ref3(new UserDefinedObject({
                                            {ObjRef(new SpecificObject<float>(2134.1234)), ObjRef(new SpecificObject<long>(1000000000))},
                                            {ObjRef(new SpecificObject<char>('c')), ObjRef(new SpecificObject<string>("beach"))},
                                            {ObjRef(new SpecificObject<string>("ketchup")), ref1},
                                            {ref2, ObjRef(new SpecificObject<double>(19.1))}
                                          }));
        ObjRef ref4(new UserDefinedObject({
                                            {ref2, ObjRef(new SpecificObject<double>(19.1))},
                                            {ObjRef(new SpecificObject<char>('c')), ObjRef(new SpecificObject<string>("beach"))},
                                            {ObjRef(new SpecificObject<string>("ketchup")), ref1},
                                            {ObjRef(new SpecificObject<float>(2134.1234)), ObjRef(new SpecificObject<long>(1000000000))},
                                          }));
        CHECK(ref3.getRO().hash() == ref4.getRO().hash());

        ObjRef expRef1(new Expression({ObjRef(new NumberObject(9.0d)), ObjRef(new SymbolObject("/")), ObjRef(new NumberObject(3.0d))}));
        ObjRef expRef2(new Expression({ObjRef(new NumberObject(9.0d)), ObjRef(new SymbolObject("/")), ObjRef(new NumberObject(3.0d))}));

        CHECK(expRef1->hash() == expRef2->hash());
    }
}

SUITE(ObjectComparison){
    TEST(Comparison){
        ObjRef uref1(new UserDefinedObject(std::unordered_map<ObjRef, ObjRef>({
                                            {ObjRef(new SpecificObject<int>(143)), ObjRef(new SpecificObject<string>("beach"))},
                                            {ObjRef(new SpecificObject<float>(534.1)), ObjRef(new SpecificObject<long>(9876))}
                                          })));
        ObjRef uref2(new UserDefinedObject({
                                            {ObjRef(new SpecificObject<float>(534.1)), ObjRef(new SpecificObject<long>(9876))},
                                            {ObjRef(new SpecificObject<int>(143)), ObjRef(new SpecificObject<string>("beach"))}
                                          }));
        CHECK(uref1 == uref2);

        ObjRef uref3(new UserDefinedObject({
                                            {ObjRef(new SpecificObject<float>(2134.1234)), ObjRef(new SpecificObject<long>(1000000000))},
                                            {ObjRef(new SpecificObject<char>('c')), ObjRef(new SpecificObject<string>("beach"))},
                                            {ObjRef(new SpecificObject<string>("ketchup")), uref1},
                                            {uref2, ObjRef(new SpecificObject<double>(19.1))}
                                          }));
        ObjRef uref4(new UserDefinedObject({
                                            {uref2, ObjRef(new SpecificObject<double>(19.1))},
                                            {ObjRef(new SpecificObject<char>('c')), ObjRef(new SpecificObject<string>("beach"))},
                                            {ObjRef(new SpecificObject<string>("ketchup")), uref1},
                                            {ObjRef(new SpecificObject<float>(2134.1234)), ObjRef(new SpecificObject<long>(1000000000))},
                                          }));
        CHECK(uref3 == uref4);

        ObjRef none1(new NoneObject);
        ObjRef none2(new NoneObject);

        CHECK(none1 == none2);
        CHECK(none1 != uref3);
        CHECK(none2 != uref2);

        ObjRef spec1(new SpecificObject<int>(9));
        ObjRef spec2(new SpecificObject<int>(9));
        ObjRef spec3(new SpecificObject<int>(10));

        ObjRef spec4(new SpecificObject<float>(5));

        CHECK(spec1 == spec2);
        CHECK(spec1 != spec3);
        CHECK(spec1 != spec4);

        CHECK(spec1 != none1);
        CHECK(spec2 != uref4);
    }
    TEST(SymbolComparison){
        ObjRef sym1(new SymbolObject("hello"));
        ObjRef sym2(new SymbolObject("hello"));
        ObjRef sym3(new SymbolObject("goodbye"));

        CHECK(sym1 == sym2);
        CHECK(sym2 != sym3);
    }
    TEST(NumberComparison){
        ObjRef num1(new NumberObject(9.234));
        ObjRef num2(new NumberObject(9.234));
        ObjRef num3(new NumberObject(-123.2));
    }
}

ObjRef testFunc(const Object& master, const Object& in){
    return ObjRef(new NoneObject);
}

SUITE(FunctorObject){
    TEST(FunctorObject){
        //ObjRef func1(new FunctorObject<Object, &testFunc>(*(new NoneObject)));
        //ObjRef none(new NoneObject);
        //CHECK(none == func1.getRO().get(none));
    }

    TEST(Plus){
        ObjRef num1(new NumberObject(8.0d));
        ObjRef num2(new NumberObject(6.0d));
        ObjRef addSym(new SymbolObject("+"));
        ObjRef result = num1->get(addSym)->get(num2);
        CHECK(result == ObjRef(new NumberObject(14.0d)));
    }
    TEST(Minus){
        ObjRef num1(new NumberObject(100.0d));
        ObjRef num2(new NumberObject(5.0d));
        ObjRef addSym(new SymbolObject("-"));
        ObjRef result = num1->get(addSym)->get(num2);
        CHECK(result == ObjRef(new NumberObject(95.0d)));
    }
    TEST(Times){
        ObjRef num1(new NumberObject(11.0d));
        ObjRef num2(new NumberObject(7.0d));
        ObjRef addSym(new SymbolObject("*"));
        ObjRef result = num1->get(addSym)->get(num2);
        CHECK(result == ObjRef(new NumberObject(77.0d)));
    }
    TEST(Divide){
        ObjRef num1(new NumberObject(5000.0d));
        ObjRef num2(new NumberObject(1000.0d));
        ObjRef addSym(new SymbolObject("/"));
        ObjRef result = num1->get(addSym)->get(num2);
        CHECK(result == ObjRef(new NumberObject(5.0d)));
    }
}

SUITE(Expression){
    TEST(StatementEvaluation){
        CHECK(Expression({ObjRef(new NumberObject(9.0d)), ObjRef(new SymbolObject("/")), ObjRef(new NumberObject(3.0d))}).evaluate() == ObjRef(new NumberObject(3.0d)));
    }
}

SUITE(parsing){
    TEST(parse){
        ObjRef expected1(new Expression(  {ObjRef(new NumberObject(9.9)), ObjRef(new SymbolObject("+")), ObjRef(new NumberObject(-45))}  ));
        vector<string> stringVec{"9.9", "+", "-45"};
        ObjRef gotten1 = parse(stringVec.begin(), stringVec.end());

        CHECK(expected1 == gotten1);
    }
    TEST(parseString){
        CHECK(parseString("1 + 5 - 2")->evaluate() == ObjRef(new NumberObject(4)));
        CHECK(parseString("1 + ( 3 * 9 )")->evaluate() == ObjRef(new NumberObject(28)));
    }
}

SUITE(evaluate){
    TEST(evaluate){
        CHECK(ObjRef(new NumberObject(4))->evaluate() == ObjRef(new NumberObject(4)));
    }
}

int main(){
    return UnitTest::RunAllTests();
}
