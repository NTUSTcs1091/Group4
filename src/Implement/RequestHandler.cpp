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

RequestHandler::RequestHandler() { this->read_size = 4096; }

void RequestHandler::SetFd(const int &file_descriptor) {
  this->client_fd = file_descriptor;
}

int RequestHandler::ReadHeader(std::string *header,
                               std::string *msg_over_header) {
  char input_buffer[this->read_size];
  const std::string find_key = "Content-Length:";
  const std::string end_of_header = "\r\n\r\n";
  // keep read buffer until no request message
  while (true) {
    int msg_read = recv(this->client_fd, input_buffer, sizeof(input_buffer), 0);
    // means end of request
    if (msg_read <= 0) {
      return -1;
    }
    // add read buffer to header
    *header += std::string(input_buffer, msg_read);
    // find \r\n\r\n to get end of header
    size_t start_cut_pos = header->find(find_key, 0) + find_key.length() + 1;
    size_t end_cut_pos = header->find(end_of_header, 0);
    if (end_cut_pos != std::string::npos) {
      size_t header_size = end_cut_pos + end_of_header.length();
      try {
        // no content_length means body size = 0
        if (start_cut_pos == std::string::npos) {
          *msg_over_header = "";
          *header = header->substr(0, header_size);
          return 0;
        }
        // convert content-length string to int
        int client_content_length = std::stoi(
            header->substr(start_cut_pos, end_cut_pos - start_cut_pos));
        // it may occur that reading too many info from buffer, need to move the
        // body part out of header message
        *msg_over_header =
            header->substr(header_size, header->length() - header_size);
        *header = header->substr(0, header_size);
        return client_content_length;
      } catch (...) {
        // TODO: call error
      }
    }
  }
}

std::string RequestHandler::ReadBody(const int &content_length,
                                     const std::string &body,
                                     std::string *next_request_part) {
  std::string result = "";
  std::string buffer_result = "";
  int string_length_needed = content_length - body.length();
  // will keep reading until complete message received
  while (string_length_needed > 0) {
    // buffer size is decided by content-length and length header has read
    char input_buffer[string_length_needed];
    int msg_read = recv(this->client_fd, input_buffer, sizeof(input_buffer), 0);
    buffer_result += std::string(input_buffer, msg_read);
    string_length_needed -= msg_read;
    if (msg_read < 0) {
      // TODO: error handle
    }
  }
  // maybe first request is too short that already get info from second header,
  // need to be removed
  result = body.substr(0, content_length) + buffer_result;
  *next_request_part =
      body.substr(content_length, body.length() - content_length);
  return result;
}

void RequestHandler::WaitForMessage() {
  // a final complete request message which will be parsed to OperateData
  std::string complete_request = "";
  std::string msg_over_header = "";
  int client_content_length = 0;
  char *input_buffer;
  // parts of message belongs to next request
  std::string next_request = "";
  while (true) {
    complete_request = next_request;
    client_content_length = ReadHeader(&complete_request, &msg_over_header);
    if (client_content_length < 0) {
      break;
    }
    complete_request +=
        ReadBody(client_content_length, msg_over_header, &next_request);
    // parse message to OperateData
    RequestParser *tmp_parser = RequestParser::GetInstance();
    this->data = tmp_parser->ParseData(complete_request);
    this->data->header["client_file_descriptor"] =
        std::to_string(this->client_fd);
    const std::string api_name = this->data->header["Method"];
    APIHandler *api_handler = RequestHandler::apis[api_name];
    if (api_handler == nullptr) {
      // should call error, wrong api calling will terminate receiving
      break;
    } else {
      api_handler->CallingAPI(std::move(this->data));
    }
  }
}
