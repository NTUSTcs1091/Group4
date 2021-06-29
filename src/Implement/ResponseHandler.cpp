// Copyright (c) 2021, 鍾淯丞, 周杰仕, 林仁鴻. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "ResponseHandler.h"

#include <sys/socket.h>

#include <iostream>

#include "OperateData.h"
#include "ResponseEncoder.h"

void ResponseHandler::Send(const std::string &for_client_fd,
                           std::unique_ptr<OperateData> data) {
  ResponseEncoder *encoder = ResponseEncoder::GetInstance();
  // Encode header and body to OperateData
  std::string response = encoder->Encode(data);

  try {
    send(std::stoi(for_client_fd), response.c_str(), response.length(), 0);
  } catch (std::invalid_argument &e) {
    std::cerr << "Client file descriptor: \"" << for_client_fd
              << "\" is wrong type!" << std::endl;
    std::cerr << e.what() << std::endl;
  }
}

ResponseHandler::ResponseHandler() {}
