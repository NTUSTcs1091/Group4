// Copyright (c) 2021, 鍾淯丞, 周杰仕, 林仁鴻. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef GROUP4_HEADER_REQUESTHANDLER_H_
#define GROUP4_HEADER_REQUESTHANDLER_H_

#include <memory.h>

#include <string>
#include <unordered_map>

#include "APIHandler.h"
#include "Authenticator.h"
#include "OperateData.h"

// Will decode the request string and check if it's a valid request.
// calling RequestParser to get OperateData then call correspond api function
class RequestHandler {
 public:
  // instantiate instance with accepted file descriptor, will receive request
  // string and parse to OperateData, then check with Authenticator and call
  // correspond api.
  RequestHandler(const int &file_descriptor);
  // receive request string and send to api
  void WaitForMessage();
  // Get client file descriptor
  int GetClientFd();
  // content of request
  std::unique_ptr<OperateData> data;
  // storing all feature api
  static const std::unordered_map<std::string, APIHandler &> apis;

//Will decode the request string and check if it's a valid request.
//calling RequestParser to get OperateData then call correspond api function
class RequestHandler
{
public:
    //instantiate instance with request, will parse to OperateData and check with Authenticator and call correspond api.
    RequestHandler(const int &file_descriptor);
    //wait for request string and call api
    void WaitForMessage();
    //content of request
    std::unique_ptr<OperateData> data;
    //storing all feature api
    static const std::unordered_map<std::string, APIHandler&> apis;
private:
    //file descriptor
    int client_fd;
};

#endif
