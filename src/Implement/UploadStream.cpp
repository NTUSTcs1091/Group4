// Copyright (c) 2021, 鍾淯丞, 周杰仕, 林仁鴻. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "UploadStream.h"

#include <fstream>
#include <string>

UploadStream::UploadStream(const std::string& filename) : filename(filename) {
  std::fstream checklock(filename + ".lock", std::fstream::in);
  if (checklock.fail()) {
    std::fstream lockfile(filename + ".lock", std::fstream::out);
    lockfile.close();
    fd.open(filename, std::ios::out | std::ios::binary | std::ios::trunc);
  } else {
    fd.setstate(std::ios::failbit);
    fd.setstate(std::ios::badbit);
  }
  checklock.close();
}

int UploadStream::AppendToFile(const std::string& binary, bool end) {
  if (fd.fail()) {
    return 0;
  }

  int half_length = binary.length() / 2;
  char buff[half_length + 1];
  buff[half_length] = '\0';

  for (int pos = 0; pos < half_length; pos++) {
    buff[pos] = '\0' + std::stoi(binary.substr(pos * 2, 2), 0, 16);
  }

  fd.write(buff, half_length);
  if (end) {
    fd.close();
    std::remove(filename.append(".lock").c_str());
  }
  return 1;
}
