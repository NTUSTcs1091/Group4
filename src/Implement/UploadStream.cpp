// Copyright (c) 2021, 鍾淯丞, 周杰仕, 林仁鴻. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "UploadStream.h"

#include <fstream>
#include <string>

UploadStream::UploadStream(const std::string& filename) : filename(filename) {
  std::fstream checklock(filename + ".lock", std::fstream::in);
  if (!checklock) {
    std::fstream lockfile(filename + ".lock", std::fstream::out);
    lockfile.close();
    fd.open(filename, std::fstream::out | std::fstream::trunc);
    fd.close();
    fd.open(filename, std::fstream::app);
    writing = true;
  }
  checklock.close();
}

int UploadStream::AppendToFile(const std::string& binary, bool end) {
  if (!writing) {
    return 0;
  }
  fd << binary;
  if (end) {
    fd.close();
    std::remove(filename.append(".lock").c_str());
  }
  return 1;
}
