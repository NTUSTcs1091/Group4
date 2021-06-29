// Copyright (c) 2021, 鍾淯丞, 周杰仕, 林仁鴻. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include <gtest/gtest.h>

#include "UploadStream.h"

// test basic usage
TEST(UPLOADSTREAM_TEST, Basic) {
  UploadStream file("test.txt");
  // check lockfile exist
  std::fstream lock("test.txt.lock", std::fstream::in);
  ASSERT_FALSE(!lock);

  // check append works fine
  file.AppendToFile("313233", true);  // 123
  std::fstream checkfile("test.txt", std::fstream::in);
  std::string content;
  checkfile >> content;
  checkfile.close();
  EXPECT_EQ("123", content);

  // check lockfile removed
  std::fstream checklock("test.txt.lock");
  EXPECT_EQ(true, !checklock);
  std::remove("test.txt");

  // test if lockfile is already exist
  std::fstream lockfile("test.lock", std::fstream::out);
  lockfile.close();
  UploadStream file2("test");
  int result = file2.AppendToFile("313233", true);
  EXPECT_EQ(0, result);
  std::remove("test.lock");
}
