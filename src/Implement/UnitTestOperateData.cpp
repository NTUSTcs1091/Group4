// Copyright (c) 2021, 鍾淯丞, 周杰仕, 林仁鴻. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "OperateData.h"

TEST(OPERATEDATA_TEST, Basic) {
  OperateData test;
  test.header.insert("method", "POST");
  test.header.insert("url", "explorer_file");
  test.header.insert("Host", "echo.paw.cloud");
  test.header.insert("Content-Type", "application/json");
  test.header.insert("User-Agent",
                     "Mozilla/5.0 (Macintosh; Intel Mac OS X 10.12; rv:53.0) "
                     "Gecko/20100101 Firefox/53.0");
  test.header.insert("Content-Length", "136");
  test.body.insert("path", "test/myFile/filename.txt");
  test.body.insert("pos", "0");
  test.body.insert("data", "123456789");
  OperateData test2 = test;
  EXPECT_EQ("POST", test2.header["method"]);
  EXPECT_EQ("explorer_file", test2.header["url"]);
  EXPECT_EQ("echo.paw.cloud", test2.header["Host"]);
  EXPECT_EQ("application/json", test2.header["Content-Type"]);
  EXPECT_EQ(
      "Mozilla/5.0 (Macintosh; Intel Mac OS X 10.12; rv:53.0) Gecko/20100101 "
      "Firefox/53.0",
      test2.header["User-Agent"]);
  EXPECT_EQ("136", test2.header["Content-Length"]);
  EXPECT_EQ("test/myFile/filename.txt", test2["path"]);
  EXPECT_EQ("0", test2["pos"]);
  EXPECT_EQ("123456789", test2["data"]);
}