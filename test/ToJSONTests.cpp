#include <gtest/gtest.h>
#include "../ToJSON.h"

TEST(ToJSONTests, TestEmptyToJSON)
{
    ToJSON::ToJSON obj;
    ASSERT_TRUE(obj.empty());
}

TEST(ToJSONTests, TestAddToJSON)
{
    ToJSON::ToJSON obj;
    obj.insert("str", "value")
        .insert("int", -3)
        .insert("float", 3.3)
        .insert("char", static_cast<char>('a'))
        .insert("unsigned int", static_cast<unsigned int>(33))
        .insert("long", static_cast<long>(1000000))
        .insert("bool", true);

    ASSERT_EQ(obj.str(), "{\"str\":\"value\",\"int\":-3,\"float\":3.3,\"char\":\"a\",\"unsigned int\":33,\"long\":1000000,\"bool\":true}");
    ASSERT_NE(obj.str(), "{int\":-3,\"float\":3.3,\"char\":\"a\",\"unsigned int\":33,\"long\":1000000}");
}

TEST(ToJSONTests, TestAddObject)
{
    ToJSON::ToJSON obj;

    ToJSON::ToJSON obj2;

    obj2.insert("hello", "goodbye");

    ToJSON::ToJSON obj3;

    obj.insert("int", -3)
        .insert("obj2", obj2)
        .insert("obj3", obj3)
        .insert("int2", 3)
        .insert("obj3", obj2);

    ASSERT_EQ(obj.str(), "{\"int\":-3,\"obj2\":{\"hello\":\"goodbye\"},\"obj3\":{},\"int2\":3,\"obj3\":{\"hello\":\"goodbye\"}}");
}

TEST(ToJSONTests, TestAddArray)
{
    ToJSON::ToJSON obj;
    ToJSON::ToArray arr;
    ToJSON::ToArray arr2;

    arr.insert_multiple(3, "g", 3.3);
    obj.insert_array("arr", 1, 3.3, false, "ok")
        .insert("int", 3)
        .insert_array("arr2")
        .insert("a1", arr)
        .insert("a2", arr2);

    ASSERT_EQ(obj.str(), "{\"arr\":[1,3.3,false,\"ok\"],\"int\":3,\"arr2\":[],\"a1\":[3,\"g\",3.3],\"a2\":[]}");
}

TEST(ToJSONTests, TestEmptyToArray)
{
    ToJSON::ToArray arr;
    ASSERT_TRUE(arr.empty());
}

TEST(ToJSONTests, TestToArrayAdd)
{
    ToJSON::ToArray arr;
    ToJSON::ToArray arr1;
    ToJSON::ToJSON obj;

    arr.insert("str")
        .insert(-3)
        .insert(3.3)
        .insert(static_cast<char>('a'))
        .insert(static_cast<unsigned int>(33))
        .insert(static_cast<long>(1000000))
        .insert(true)
        .insert(arr1)
        .insert(obj);

    ASSERT_EQ(arr.str(), "[\"str\",-3,3.3,\"a\",33,1000000,true,[],{}]");
}
