#pragma once

#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>

#include <jsonobject.h>
#include <QFile>

using namespace testing;

#include <QTest>


class JsonObjectTest : public ::testing::Test
{
protected:
    virtual void SetUp()
    {
        jsonObject = tnk::JsonObject();
    }
    virtual void TearDown()
    {

    }

    tnk::JsonObject jsonObject;
};


TEST_F(JsonObjectTest, setvalue)
{
    jsonObject.setValue("test/foo/bar", 42);
    EXPECT_EQ(jsonObject.value("test/foo/bar").toInt(), 42);
}


TEST_F(JsonObjectTest, write_read)
{
    QFile::remove("test.json");
    jsonObject.setValue("test/foo/bar", 42);
    jsonObject.save("test.json");

    EXPECT_EQ(QFile::exists( "test.json"), true);

    jsonObject = tnk::JsonObject();
    EXPECT_EQ(jsonObject.value("test/foo/bar").toInt(), 0);

    jsonObject.load("test.json");
    EXPECT_EQ(jsonObject.value("test/foo/bar").toInt(), 42);

    QFile::remove("test.json");
}


