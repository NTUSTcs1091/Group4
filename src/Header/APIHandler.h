// Copyright (c) 2021, 鍾淯丞, 周杰仕, 林仁鴻. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef GROUP4_HEADER_APIHANDLER_H_
#define GROUP4_HEADER_APIHANDLER_H_

#include <string>

#include "OperateData.h"

// an interface for all the api which are our main services
class APIHandler {
 public:
  APIHandler();
  // the start entry of all api services
  virtual void CallingAPI(const OperateData& data);
  // non copyable
  APIHandler(const APIHandler&) = delete;
  APIHandler& operator=(const APIHandler&) = delete;

 private:
  // will generate response after service end or an error occured.
  OperateData response;
};

#endif
