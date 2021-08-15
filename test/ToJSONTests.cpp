#include <gtest/gtest.h>
#include "../ToJSON.h"

TEST(ToJSONTests, TestEmptyToJSON)
{
    ToJSON::ToJSON obj;
    ASSERT_TRUE(obj.empty());
}

TEST(ToJSONTests, TestEmptyToArray)
{
    ToJSON::ToArray arr;
    ASSERT_TRUE(arr.empty());
}

TEST(ToJSONTests, TestAddToJSON)
{
    ToJSON::ToJSON obj;
    obj.add("str", "value")
        .add("int", -3)
        .add("float", 3.3)
        .add("char", static_cast<char>('a'))
        .add("unsigned int", static_cast<unsigned int>(33))
        .add("long", static_cast<long>(1000000))
        .add("bool", true);

    ASSERT_EQ(obj.str(), "{\"str\":\"value\",\"int\":-3,\"float\":3.3,\"char\":\"a\",\"unsigned int\":33,\"long\":1000000,\"bool\":true}");
    ASSERT_NE(obj.str(), "{int\":-3,\"float\":3.3,\"char\":\"a\",\"unsigned int\":33,\"long\":1000000}");
}

TEST(ToJSONTests, TestAddObject)
{
    ToJSON::ToJSON obj;

    ToJSON::ToJSON obj2;

    obj2.add("hello", "goodbye");

    ToJSON::ToJSON obj3;

    obj.add("int", -3)
        .add("obj2", obj2)
        .add("obj3", obj3)
        .add("int2", 3)
        .add("obj3", obj2);

    ASSERT_EQ(obj.str(), "{\"int\":-3,\"obj2\":{\"hello\":\"goodbye\"},\"obj3\":{},\"int2\":3,\"obj3\":{\"hello\":\"goodbye\"}}");
}

TEST(ToJSONTests, TestAddArray)
{
    ToJSON::ToJSON obj;
    obj.add_array("arr", 1, 3.3, false, "ok")
        .add("int", 3)
        .add_array("arr2");

    ASSERT_EQ(obj.str(), "{\"arr\":[1,3.3,false,\"ok\"],\"int\":3,\"arr2\":[]}");
}