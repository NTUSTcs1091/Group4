// Copyright (c) 2021, 鍾淯丞, 周杰仕, 林仁鴻. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "RequestParser.h"

RequestParser* RequestParser::only_request_parser = nullptr;

RequestParser* RequestParser::GetInstance() {
  if (only_request_parser == nullptr) {
    only_request_parser = new RequestParser();
  }
  return only_request_parser;
}

// normally http content which will be received in string type
/*
POST /?id=1 HTTP/1.1
Host: echo.paw.cloud
Content-Type: application/json; charset=utf-8
User-Agent: Mozilla/5.0 (Macintosh; Intel Mac OS X 10.12; rv:53.0)
Gecko/20100101 Firefox/53.0 Connection: close Content-Length: 136

{
  "status": "ok",
  "extended": true,
  "results": [
    {"value": 0, "type": "int64"},
    {"value": 1.0e+3, "type": "decimal"}
  ]
}
*/
OperateData* RequestParser::ParseData(const std::string& request) {
  OperateData* new_data = new OperateData();
  new_data->header["method"] = request.substr(0, request.find(" "));
  size_t url_key_start = request.find(" ") + 2;
  size_t url_key_end = request.find(" ", request.find(" ") + 1);
  new_data->header["url"] =
      request.substr(url_key_start, url_key_end - url_key_start);
  for (int i = 0; i < new_data->header["url"].length(); i++) {
    if (new_data->header["url"][i] == '/') {
      new_data->header["url"].replace(i, 1, "_");
    }
  }
  size_t body_start_pos = request.find("{");
  size_t body_end_pos = request.find("}");
  size_t iterate_index = body_start_pos;
  while (iterate_index < body_end_pos) {
    size_t key_start = request.find('"', iterate_index) + 1;
    size_t key_end = request.find('"', key_start);
    size_t value_start = request.find('"', key_end + 1) + 1;
    size_t value_end = request.find('"', value_start);
    new_data->body[request.substr(key_start, key_end - key_start)] =
        request.substr(value_start, value_end - value_start);
    iterate_index = value_end + 1;
  }
  return new_data;
}

RequestParser::RequestParser() {}