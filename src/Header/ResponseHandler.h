// Copyright (c) 2021, 鍾淯丞, 周杰仕, 林仁鴻. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef GROUP4_SRC_RESPONSEHANDLER_H_
#define GROUP4_SRC_RESPONSEHANDLER_H_

#include <string>

#include "Logger.h"
#include "OperateData.h"
#include "ResponseEncoder.h"
#include "ResponseParser.h"


// Handle response and call corresponding service
class ResponseHandler {
 public:
  // Constructor
  ResponseHandler();

  // Send data and header to corresponding service
  void Send(Service service);

  // Not copyable or movable
  ResponseHandler(const ResponseHandler &copy) = delete;
  ResponseHandler &operator=(const ResponseHandler &copy) = delete;

 private:
  // A variable to storage OperatorData data
  OperatorData data;
  // A variable to storage OperatorData header
  OperatorData header;
  // A variable to storage response information
  std::string response;
};

#endif /* GROUP4_SRC_RESPONSEHANDLER_H_ */
