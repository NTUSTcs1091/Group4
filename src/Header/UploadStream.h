// Copyright (c) 2021, 鍾淯丞, 周杰仕, 林仁鴻. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef GROUP4_HEADER_UploadStream_H_
#define GROUP4_HEADER_UploadStream_H_

#include <fstream>
#include <string>

// write file to local may use a lock file or system call to signify that a
// certain file is currently in use.
class UploadStream {
 public:
  // filename will include file path,
  UploadStream(const std::string& filename);
  // This function will only append binary at the end of the file, so
  // user should handle the order yourself. If it run successfully, it will
  // return 1 else 0. If end is True, then it will close the file.
  int AppendToFile(const std::string& binary, bool end);
  // non copyable
  UploadStream(const UploadStream&) = delete;
  UploadStream& operator=(const UploadStream&) = delete;

 private:
  // will point to the same file
  std::fstream fd;
  // filename include file path
  std::string filename;
  // True indicate that it has the write access of the file, otherwise.
  bool writing = false;
};

#endif
