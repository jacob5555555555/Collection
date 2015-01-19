#include <unittest++/UnitTest++.h>

#include <Tokenizer.h>
#include <LazyCopyRef.h>
#include <SpecificObject.h>
#include <UserDefinedObject.h>
#include <string>

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
    }
}

int main(){
    return UnitTest::RunAllTests();
}
