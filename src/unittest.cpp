#include <unittest++/UnitTest++.h>

#include <Tokenizer.h>
#include <LazyCopyRef.h>
#include <SpecificObject.h>
#include <UserDefinedObject.h>
#include <string>
#include <SymbolObject.h>
#include <NumberObject.h>

using namespace std;

//tests

SUITE(LazyCopyRef){
    LazyCopyRef<int> make14(){
        return LazyCopyRef<int>(new int(14));
    }
    TEST(CopyAndDereference){
        LazyCopyRef<int> i1(new int(5));
        LazyCopyRef<int> i2(i1);
        LazyCopyRef<int> i3(i2);
        i3.get() = 3;
        LazyCopyRef<int> i4 = make14();

        CHECK(i1.getRO() == 5);
        CHECK(i2.getRO() == 5);
        CHECK(i3.getRO() == 3);
        CHECK(i4.getRO() == 14);
    }

    TEST(OnlyCopyWhenNeed){
        LazyCopyRef<string> strRef(new string("pork"));
        LazyCopyRef<string> strRef2 = strRef;
        CHECK( &(strRef.getRO()) == &(strRef2.getRO()) );
        CHECK(strRef.getRO() == "pork");
        CHECK(strRef2.getRO() == "pork");
        CHECK( &(strRef.getRO()) == &(strRef2.getRO()) );
        strRef2.get() = "bacon";
        CHECK(strRef.getRO() == "pork");
        CHECK(strRef2.getRO() == "bacon");
        CHECK( &(strRef.getRO()) != &(strRef2.getRO()) );
    }
}

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

int main(){
    return UnitTest::RunAllTests();
}
