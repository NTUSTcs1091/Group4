// Copyright (c) 2021, 鍾淯丞, 周杰仕, 林仁鴻. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include <arpa/inet.h>
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#include <functional>
#include <thread>

#include "RequestHandler.h"

void TestClient() {
  int sockfd = 0;
  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  struct sockaddr_in info;
  bzero(&info, sizeof(info));
  info.sin_family = PF_INET;
  info.sin_addr.s_addr = inet_addr("127.0.0.1");
  info.sin_port = htons(9000);
  int err = connect(sockfd, (struct sockaddr *)&info, sizeof(info));
  std::string test_body = "";
  test_body += "{";
  test_body += "\"path\":\"testPath/myFile/filename.txt\",";
  test_body += "\"pos\":\"0\",";
  test_body += "\"data\":\"0123456789\"";
  test_body += "}";
  std::string test_string = "POST /explorer/file HTTP/1.1\n";
  test_string += "Host: echo.paw.cloud\n";
  test_string += "Content-Type: application/json; charset=utf-8\n";
  test_string +=
      "User-Agent: Mozilla/5.0 (Macintosh; Intel Mac OS X 10.12; rv:53.0) ";
  test_string += "Gecko/20100101 Firefox/53.0\n";
  test_string += "Connection: close\n";
  test_string +=
      "Content-Length: " + std::to_string(test_body.length()) + "\r\n\r\n";
  test_string += test_body;
  const char *message = test_string.c_str();
  send(sockfd, message, test_string.length(), 0);
  close(sockfd);
}

TEST(TEST_RequestHandler, GetMessage_Short) {
  int server_fd = socket(AF_INET, SOCK_STREAM, 0);
  struct sockaddr_in socket_info;
  bzero((struct sockaddr *)&socket_info, sizeof(socket_info));
  socket_info.sin_family = PF_INET;
  socket_info.sin_addr.s_addr = INADDR_ANY;
  socket_info.sin_port = htons(9000);
  bind(server_fd, (struct sockaddr *)&socket_info,
       (socklen_t)sizeof(socket_info));
  listen(server_fd, 1);
  struct sockaddr_in client_socket_info;
  socklen_t addr_len = sizeof(client_socket_info);
  TestClient();
  int client_fd =
      accept(server_fd, (struct sockaddr *)&client_socket_info, &addr_len);
  RequestHandler request_handler = RequestHandler(client_fd);
  std::thread test_wait =
      std::thread(&RequestHandler::WaitForMessage, &request_handler);
  sleep(1);
  EXPECT_EQ("POST", request_handler.data->header["method"]);
  EXPECT_EQ("explorer_file", request_handler.data->header["url"]);
  EXPECT_EQ("testPath/myFile/filename.txt", request_handler.data->body["path"]);
  EXPECT_EQ("0", request_handler.data->body["pos"]);
  EXPECT_EQ("0123456789", request_handler.data->body["data"]);
  test_wait.join();
}
