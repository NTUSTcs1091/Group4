// Copyright (c) 2021, 鍾淯丞, 周杰仕, 林仁鴻. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef GROUP4_SRC_REQUESTPARSER_H_
#define GROUP4_SRC_REQUESTPARSER_H_

#include <string>
#include <memory>

#include "OperateData.h"

//used to make request string to OperateData(JSON like) format.
//string requestStr = "GET /?token=111 HTTP/1.1\n"
//unique_ptr<OperateData> data = RequestParser::ParserHeader(requestStr)
//data will return header and body.
class RequestParser
{
public:
    //singleton code convention method.
    static unique_ptr<RequestParser> GetInstance();
    //give request string return body / data
    unique_ptr<OperateData> ParseData(const std::string &request);
private:
    //singleton code convention method.
    RequestParser();
};

#endif
