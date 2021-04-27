// Copyright (c) 2021, 鍾淯丞, 周杰仕, 林仁鴻. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef GROUP4_SRC_RESPONSEPARSER_H_
#define GROUP4_SRC_RESPONSEPARSER_H_

#include <memory>
#include <string>

#include "OperateData.h"

/*
    // Used to make request string to OperateData format.
    string responseStr = "HTTP/1.1 201 Created
                          Server: libnhttpd
                          Date: Wed Jul 4 15:31:53 2012
                          Connection: Keep-Alive
                          Content-Type: application/json;charset=UTF-8
                          Content-Length: 304
                          {
                              packet-num: 5
                          }"
    ResponseParser* response_parser = ResponseParser::GetInstance();
    std::unique_ptr<OperateData> result = response_parser->ParseData(test_string);
*/

class ResponseParser {
public:
    // Singleton code convention method
    static ResponseParser* GetInstance();
    
    // Give request string return header
    std::unique_ptr<OperateData> ParseData(std::string &response);
    
    // Not copyable or movable
    ResponseParser(const ResponseParser &copy) = delete;
    ResponseParser& operator = (const ResponseParser &copy) = delete;
    
private:
    // Singleton code convention method
    ResponseParser();
};

#endif /* GROUP4_SRC_RESPONSEPARSER_H_ */
