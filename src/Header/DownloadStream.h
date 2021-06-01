// Copyright (c) 2021, 鍾淯丞, 周杰仕, 林仁鴻. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef GROUP4_HEADER_DownloadStream_H_
#define GROUP4_HEADER_DownloadStream_H_

#include <fstream>
#include <string>

// read file from local
class DownloadStream {
 public:
  // filename will include file path, set a default chunk size
  DownloadStream(const std::string &filename, const unsigned long &chunk_size);
  // if run successfully, it will return 1 else return 0
  int ReadChunk(unsigned long &pos, std::string *const binary);
  // non cpoyable
  DownloadStream(const DownloadStream &) = delete;
  DownloadStream &operator=(const DownloadStream &) = delete;

 private:
  // will point to the same file
  std::fstream fd;
  // filename include file path
  std::string filename;
  // default chunk size
  unsigned long chuck_size;
};

#endif
