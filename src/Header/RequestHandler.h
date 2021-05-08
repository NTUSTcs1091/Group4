// Copyright (c) 2021, 鍾淯丞, 周杰仕, 林仁鴻. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef GROUP4_HEADER_REQUESTHANDLER_H_
#define GROUP4_HEADER_REQUESTHANDLER_H_

#include <memory>
#include <string>
#include <unordered_map>

#include "OperateData.h"
#include "Authenticator.h"
#include "APIHandler.h"


//Will decode the request string and check if it's a valid request.
//calling RequestParser to get OperateData then call correspond api function
class RequestHandler
{
public:
    //instantiate instance with request, will parse to OperateData and check with Authenticator and call correspond api.
    RequestHandler(const std::string &requestData);
    //content of request
    std::unique_ptr<OperateData> data;
    //storing all feature api
    static const std::unordered_map<std::string, APIHandler&> apis;
};

#endif
