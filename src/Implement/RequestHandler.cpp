// Copyright (c) 2021, 鍾淯丞, 周杰仕, 林仁鴻. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "RequestHandler.h"

#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#include <string>

std::unordered_map<std::string, APIHandler *> RequestHandler::apis;

RequestHandler::RequestHandler(const int &file_descriptor) {
  this->client_fd = file_descriptor;
}

void RequestHandler::WaitForMessage() {
  std::string tmp_string = "";
  char input_buffer[4096] = {};
  std::string next_request = "";
  // only read header if message is bigger than buffer
  while (true) {
    int function_flag =
        recv(this->client_fd, input_buffer, sizeof(input_buffer), 0);
    if (function_flag > 0) {
      std::string to_str = next_request + input_buffer;
      std::string find_key = "Content-Length:";
      size_t start_cut_pos = to_str.find(find_key, 0) + find_key.length();
      size_t end_cut_pos = to_str.find("\r\n\r\n", 0);
      // keep adding message until find Content-Length
      if (to_str.find(find_key, 0) != std::string::npos) {
        // get content length
        int client_content_length = std::stoi(
            to_str.substr(start_cut_pos, end_cut_pos - start_cut_pos));
        tmp_string += to_str.substr(0, end_cut_pos + 4 + client_content_length);
        next_request = to_str.substr(
            end_cut_pos + 4 + client_content_length,
            to_str.length() - (end_cut_pos + 4 + client_content_length));
        // parse message to OperateData
        RequestParser *tmp_parser = RequestParser::GetInstance();
        this->data = tmp_parser->ParseData(tmp_string);
        this->data->header["client_file_descriptor"] =
            std::to_string(this->client_fd);
        const std::string api_name = this->data->header["Method"];
        APIHandler *api_handler = RequestHandler::apis[api_name];
        if (api_handler == nullptr) {
          // should call error, wrong api calling will terminate receiving
          // printf("no such function\n");
          break;
        } else {
          api_handler->CallingAPI(std::move(this->data));
        }
        tmp_string = "";
      } else {
        tmp_string += input_buffer;
      }
    } else if (function_flag == 0) {
      // end of request
      break;
    } else {
      // connection error
      // TODO: calling log
    }
    sleep(0.2);
  }
}