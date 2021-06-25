// Copyright (c) 2021, 鍾淯丞, 周杰仕, 林仁鴻. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef GROUP4_SRC_HEADER_FILEOPERATOR_H_
#define GROUP4_SRC_HEADER_FILEOPERATOR_H_

#include <string>

#include "APIHandler.h"
#include "OperateData.h"
#include "ResponseHandler.h"

// File management for client
class FileOperator : public APIHandler {
 public:
  // Constructor
  FileOperator();

  // Upload file to server.
  int Upload(std::unique_ptr<OperateData> data);

  // Down file to client.
  int Download(std::unique_ptr<OperateData> data, std::string &file_content);

  // Use key "Method" of OperateData to call API
  void CallingAPI(std::unique_ptr<OperateData> data) override;

  // Not copyable or movable
  FileOperator(const FileOperator &copy) = delete;
  FileOperator &operator=(const FileOperator &copy) = delete;

 private:
  // Use ResponseHandler to call corresponding service
  ResponseHandler response_handler;
};

#endif  // GROUP4_SRC_HEADER_FILEOPERATOR_H_
