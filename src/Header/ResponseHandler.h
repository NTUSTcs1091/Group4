// Copyright (c) 2021, 鍾淯丞, 周杰仕, 林仁鴻. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef GROUP4_SRC_HEADER_RESPONSEHANDLER_H_
#define GROUP4_SRC_HEADER_RESPONSEHANDLER_H_

#include <memory>
#include <string>

#include "OperateData.h"

// Handle response and call corresponding service
class ResponseHandler {
 public:
  // Constructor
  ResponseHandler();

  // Send data and header to corresponding service
  void Send(const std::string &for_client_fd,
            std::unique_ptr<OperateData> data);

  // Not copyable or movable
  ResponseHandler(const ResponseHandler &copy) = delete;
  ResponseHandler &operator=(const ResponseHandler &copy) = delete;
};

#endif /* GROUP4_SRC_HEADER_RESPONSEHANDLER_H_ */
