// Copyright (c) 2021, 鍾淯丞, 周杰仕, 林仁鴻. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include <arpa/inet.h>
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <netinet/in.h>
#include <unistd.h>

#include <memory>
#include <thread>

#include "OperateData.h"
#include "ResponseHandler.h"

namespace {
const uint16_t test_port = 9003;
std::string temp_response = "";

void TestClient() {
  int sockfd = 0;
  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  struct sockaddr_in info;
  bzero(&info, sizeof(info));
  info.sin_family = PF_INET;
  info.sin_addr.s_addr = inet_addr("127.0.0.1");
  info.sin_port = htons(test_port);
  int err = connect(sockfd, (struct sockaddr *)&info, sizeof(info));

  char buffer[2048] = {};
  size_t n_recv = recv(sockfd, buffer, sizeof(buffer), 0);

  temp_response = buffer;

  close(sockfd);
}
}  // namespace

// test with a sudo string data
TEST(RESPONSEHANDLER_TEST, Basic) {
  int server_fd = socket(AF_INET, SOCK_STREAM, 0);
  struct sockaddr_in socket_info;
  bzero((struct sockaddr *)&socket_info, sizeof(socket_info));
  socket_info.sin_family = PF_INET;
  socket_info.sin_addr.s_addr = INADDR_ANY;
  socket_info.sin_port = htons(test_port);
  bind(server_fd, (struct sockaddr *)&socket_info,
       (socklen_t)sizeof(socket_info));
  listen(server_fd, 1);
  struct sockaddr_in client_socket_info;
  socklen_t addr_len = sizeof(client_socket_info);

  // Multi-thread
  std::thread test_client(TestClient);

  int client_fd =
      accept(server_fd, (struct sockaddr *)&client_socket_info, &addr_len);

  std::unique_ptr<OperateData> response = std::make_unique<OperateData>();
  response->header["status_code"] = "500";
  response->body["success"] = "False";
  response->body["error_message"] = "Something error occurred in POST method.";

  ResponseHandler response_handler;
  // Send to client
  response_handler.Send(std::to_string(client_fd), std::move(response));
  test_client.join();
  std::string correct_response = "HTTP/1.1 500 Internal Server Error\n";
  correct_response += "{\n";
  correct_response +=
      "\terror_message: Something error occurred in POST method.\n";
  correct_response += "\tsuccess: False\n";
  correct_response += "}\n";

  EXPECT_EQ(correct_response, temp_response);
  close(server_fd);
}
