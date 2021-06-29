// Copyright (c) 2021, 鍾淯丞, 周杰仕, 林仁鴻. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "DownloadStream.h"

#include <fstream>
#include <iomanip>
#include <sstream>
#include <string>

DownloadStream::DownloadStream(const std::string &filename,
                               const unsigned long &chunk_size)
    : filename(filename), chunk_size(chunk_size) {
  fd.open(filename, std::ios::in | std::ios::binary);
  if (!fd.fail()) {
    fd.seekg(0, std::ios::end);
    sstream_size = fd.tellg();
    // read hexa with white-space
    fd >> std::noskipws;
    if (sstream_size > chunk_size) {
      sstream_size = chunk_size;
    }
  }
}

int DownloadStream::ReadChunk(unsigned long &pos, std::string *const binary) {
  if (fd.fail()) {
    return 0;
  }
  fd.seekg(pos * sstream_size, std::ios::beg);
  // use for loop to change each unsigned char to byte information
  unsigned char one_byte;
  fd >> std::noskipws;
  std::stringstream ss;
  for (int buffer_pos = 0; buffer_pos < sstream_size; buffer_pos++) {
    fd >> one_byte;
    ss << std::hex << std::setw(2) << std::setfill('0') << (int)one_byte;
  }
  *binary = ss.str();
  if (fd.eof()) {
    return 2;
  }
  return 1;
}
