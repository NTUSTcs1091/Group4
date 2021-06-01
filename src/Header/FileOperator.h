// Copyright (c) 2021, 鍾淯丞, 周杰仕, 林仁鴻. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef GROUP4_SRC_FILEOPERATOR_H_
#define GROUP4_SRC_FILEOPERATOR_H_

#include <string>

#include "OperateData.h"
#include "ResponseHandler.h"
#include "StreamConnector.h"

// File management for client
class FileOperator {
 public:
  // Constructor
  FileOperator();

  // Upload file to server.
  void Upload(const std::string &path, const std::string &filename,
              const std::string &host, const int &port);

  // Down file to client.
  void Download(const std::string &path, const std::string &host,
                const int &port);

  // Update file info. For example, file name or owner, file authority.
  void Update(const std::string &path, const &OperatorData updateInfo,
              const std::string &host, const int &port);

  // Not copyable or movable
  FileOperator(const FileOperator &copy) = delete;
  FileOperator &operator=(const FileOperator &copy) = delete;

 private:
  // Use ResponseHandler to call corresponding service
  ResponseHandler response;
};

#endif  // GROUP4_SRC_FILEOPERATOR_H_
