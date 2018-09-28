#pragma once

#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>

#include <utils.h>
#include <QFile>

using namespace testing;

TEST(utils, fileTest)
{
    QFile::remove("test.txt");

    QByteArray data = QByteArray("dfuilgvudfklghd,iomhgduihbomdivbjmwxobj,");
    tnk::utils::toFile("test.txt", data);

    QByteArray result = tnk::utils::fromFile("test.txt");

    EXPECT_EQ(data, result);

    QFile::remove("test.txt");
}


