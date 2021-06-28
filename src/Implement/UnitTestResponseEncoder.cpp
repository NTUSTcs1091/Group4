// Copyright (c) 2021, 鍾淯丞, 周杰仕, 林仁鴻. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <memory>

#include "OperateData.h"
#include "ResponseEncoder.h"

// test with a sudo string data
TEST(RESPONSEENCODER_TEST, Basic) {
  std::unique_ptr<OperateData> operate_data = std::make_unique<OperateData>();
  operate_data->header["status_code"] = "200";
  operate_data->body["success"] = "True";
  operate_data->body["service"] = "Upload";
  ResponseEncoder* response_encoder = ResponseEncoder::GetInstance();
  std::string encode_result = response_encoder->Encode(operate_data);

  std::string correct_respone = "HTTP/1.1 200 OK\n";
  correct_respone += "Content-Length: 44\n";
  correct_respone += "Content-Type: application/json\n";
  correct_respone += "Connection: Closed\n\n";
  correct_respone += "{\n";
  correct_respone += "\"service\": \"Upload\",\n";
  correct_respone += "\"success\": \"True\",\n";
  correct_respone += "}\n";

  EXPECT_EQ(correct_respone,
            encode_result.substr(0, encode_result.find("Date", 0)) +
                encode_result.substr(encode_result.find("Content-Length", 0),
                                     std::string::npos));
}
