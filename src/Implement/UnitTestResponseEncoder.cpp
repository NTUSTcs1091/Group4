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
  EXPECT_EQ("HTTP/1.1 200 OK\n{\n\tservice: Upload\n\tsuccess: True\n}\n",
            encode_result);
}
