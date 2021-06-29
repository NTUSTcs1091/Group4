// Copyright (c) 2021, 鍾淯丞, 周杰仕, 林仁鴻. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "ResponseEncoder.h"

#include "OperateData.h"

ResponseEncoder* only_response_encoder = nullptr;

ResponseEncoder* ResponseEncoder::GetInstance() {
  if (only_response_encoder == nullptr) {
    only_response_encoder = new ResponseEncoder();
  }
  return only_response_encoder;
}

std::string ResponseEncoder::Encode(const std::unique_ptr<OperateData>& data) {
  std::string result_response = "HTTP/1.1 " + data->header["status_code"] + " ";

  if (std::stoi(data->header["status_code"]) == 200)
    result_response += "OK\n";
  else
    result_response += "Internal Server Error\n";

  std::string result_response_body = "{\n";
  for (auto kv : data->body) {
    result_response_body +=
        '"' + kv.first + "\": " + '"' + kv.second + "\"," + '\n';
  }
  result_response_body += "}\n";

  for (auto kv : data->header) {
    if (kv.first == "status_code" || kv.first == "status") continue;
    result_response += kv.first + ": " + kv.second + '\n';
  }
  char buf[30];
  buf[29] = '\0';
  time_t now = time(0);
  struct tm tm = *gmtime(&now);
  strftime(buf, 30, "%a, %d %b %Y %H:%M:%S %Z", &tm);
  result_response = result_response + "Date: " + buf + '\n';
  result_response +=
      "Content-Length: " + std::to_string(result_response_body.length()) + '\n';
  result_response += "Content-Type: application/json\n";
  result_response += "Connection: Closed\n\n";

  result_response += result_response_body;

  return result_response;
}

ResponseEncoder::ResponseEncoder() {}
