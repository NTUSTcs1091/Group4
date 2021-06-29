// Copyright (c) 2021, 鍾淯丞, 周杰仕, 林仁鴻. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include <gtest/gtest.h>

#include "DownloadStream.h"

// test basic usage
TEST(DOWNLOADSTREAM_TEST, Basic) {
  // create temporary test file
  std::fstream newfile("test", std::ios::out | std::ios::binary);
  constexpr char kTestFileContent[] =
      "\x31\x32\x33\x0A\x0A\x34\x35\x36";  // "123\n\n456"
  newfile << kTestFileContent;
  newfile.close();
  int file_length = sizeof(kTestFileContent) / sizeof(char);

  DownloadStream down("test", 1);
  unsigned long pos = 0;
  std::string binary;
  int result;

  // check ReadChunk
  std::string temp = "";
  for (pos = 0; pos < file_length - 1; pos++) {
    result = down.ReadChunk(pos, &binary);
    ASSERT_EQ(1, result);
    EXPECT_EQ(kTestFileContent[pos],
              static_cast<char>(std::stoi(binary, 0, 16)));
  }
  // check EOF
  result = down.ReadChunk(pos, &binary);
  ASSERT_EQ(2, result);

  std::remove("test");
}
