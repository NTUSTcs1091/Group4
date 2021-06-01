// Copyright (c) 2021, 鍾淯丞, 周杰仕, 林仁鴻. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef GROUP4_SRC_RESPONSEPARSER_H_
#define GROUP4_SRC_RESPONSEPARSER_H_

#include <memory>
#include <string>

#include "OperateData.h"

// Used to make request string to OperateData(JSON like) format.
// string responseStr = "[X: X_DATA, Y: Y_DATA]"
// unique_ptr<OperateData> data = RequestParser::ParserHeader(responseStr)
// data will return header and body.
class ResponseParser {
 public:
  // Singleton code convention method
  static RequestParser *GetInstance();

  // Give request string return header
  std::unique_ptr<OperateData> ParseHeader(std::string &response);

  // Give request string return body
  std::unique_ptr<OperateData> ParseBody(std::string &response);

  // Not copyable or movable
  ResponseParser(const ResponseParser &copy) = delete;
  ResponseParser &operator=(const ResponseParser &copy) = delete;

 private:
  // Singleton code convention method
  ResponseParser();
};

#endif /* GROUP4_SRC_RESPONSEPARSER_H_ */
