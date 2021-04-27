// Copyright (c) 2021, 鍾淯丞, 周杰仕, 林仁鴻. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "ResponseParser.h"
#include "OperateData.h"

ResponseParser* only_response_parser = nullptr;

ResponseParser* ResponseParser::GetInstance() {
  if (only_response_parser == nullptr) {
    only_response_parser = new ResponseParser();
  }
  return only_response_parser;
}

// Normally http content which will be received in string type
/*
 HTTP/1.1 201 Created
 Server: libnhttpd
 Date: Wed Jul 4 15:31:53 2012
 Connection: Keep-Alive
 Content-Type: application/json;charset=UTF-8
 Content-Length: 304
 {
    packet-num: 5
 }
*/

std::unique_ptr<OperateData> ResponseParser::ParseData(std::string &response) {
    std::unique_ptr<OperateData> new_data = std::make_unique<OperateData>();
    
    // Get status code
    size_t status_code_start = response.find(" ") + 1;
    size_t status_code_end = response.find(" ", status_code_start);
    new_data->header["status_code"] = response.substr(status_code_start, status_code_end - status_code_start);
    
    // Get status
    new_data->header["status"] = response.substr(status_code_end + 1, response.find('\n') - status_code_end - 1);
    
    // Use Anonymous function to get header value
    auto get_header_value_by_key = [] (std::string response, std::string header_key) {
        size_t header_value_start = response.find(header_key) + header_key.length() + 2;
        size_t header_value_end = response.find('\n', response.find(header_key)) - header_value_start;
        return response.substr(header_value_start, header_value_end);
    };
    
    // Get header value
    new_data->header["Server"] = get_header_value_by_key(response, "Server");
    new_data->header["Date"] = get_header_value_by_key(response, "Date");
    new_data->header["Connection"] = get_header_value_by_key(response, "Connection");
    new_data->header["Content-type"] = get_header_value_by_key(response, "Content-Type");
    new_data->header["Content-length"] = get_header_value_by_key(response, "Content-Length");
    
    // Parse body
    size_t body_start_pos = response.find("{");
    size_t body_end_pos = response.find("}");
    size_t iterate_index = body_start_pos;
    
    // All the json key and value is string, so will be cut by finding "
    // Each loop will get a key and a value
    while (iterate_index < body_end_pos) {
        size_t key_start = response.find('"', iterate_index) + 1;
        size_t key_end = response.find('"', key_start);
        size_t value_start = response.find('"', key_end + 1) + 1;
        size_t value_end = response.find('"', value_start);
        new_data->body[response.substr(key_start, key_end - key_start)] = response.substr(value_start, value_end - value_start);
        iterate_index = value_end + 1;
    }

    return new_data;
}

ResponseParser::ResponseParser() {

}
