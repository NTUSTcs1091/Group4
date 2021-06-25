//// Copyright (c) 2021, 鍾淯丞, 周杰仕, 林仁鴻. All rights reserved.
//// Use of this source code is governed by a BSD-style license that can be
//// found in the LICENSE file.
//
//#include <arpa/inet.h>
//#include <netinet/in.h>
//#include <unistd.h>
//
//#include <memory>
//#include <thread>
//
//#include <gmock/gmock.h>
//#include <gtest/gtest.h>
//
//#include "FileOperator.h"
//#include "OperateData.h"
//
// namespace  {
//    const uint16_t test_port = 9000;
//    std::string temp_response = "";
//
//    void TestClient() {
//        int sockfd = 0;
//        sockfd = socket(AF_INET, SOCK_STREAM, 0);
//        struct sockaddr_in info;
//        bzero(&info, sizeof(info));
//        info.sin_family = PF_INET;
//        info.sin_addr.s_addr = inet_addr("127.0.0.1");
//        info.sin_port = htons(test_port);
//        int err = connect(sockfd, (struct sockaddr *)&info, sizeof(info));
//
//        char buffer[2048] = {};
//        size_t n_recv = recv(sockfd, buffer, sizeof(buffer), 0);
//
//        temp_response = buffer;
//
//        close(sockfd);
//    }
//}
//
//// test with a sudo string data
// TEST(FILEOPERATOR_TEST, Basic) {
//    int server_fd = socket(AF_INET, SOCK_STREAM, 0);
//    struct sockaddr_in socket_info;
//    bzero((struct sockaddr *)&socket_info, sizeof(socket_info));
//    socket_info.sin_family = PF_INET;
//    socket_info.sin_addr.s_addr = INADDR_ANY;
//    socket_info.sin_port = htons(test_port);
//    bind(server_fd, (struct sockaddr *)&socket_info,
//       (socklen_t)sizeof(socket_info));
//    listen(server_fd, 1);
//    struct sockaddr_in client_socket_info;
//    socklen_t addr_len = sizeof(client_socket_info);
//
//    // Multi-thread
//    std::thread test_client(TestClient);
//
//    int client_fd =
//          accept(server_fd, (struct sockaddr *)&client_socket_info,
//          &addr_len);
//
//    std::unique_ptr<OperateData> operate_data =
//    std::make_unique<OperateData>();
//
//    operate_data->header["client_file_descriptor"] =
//    std::to_string(client_fd);; operate_data->header["method"] = "POST";
//    operate_data->header["url"] = "http://test.com";
//    operate_data->body["path"] = "usr/local/test.txt";
//    operate_data->body["data"] = "a";
//    operate_data->body["is_end"] = "true";
//
//    FileOperator fo;
//    fo.CallingAPI(std::move(operate_data));
//
//    test_client.join();
//
//    std::string correct_response = "HTTP/1.1 200 OK\n";
//    correct_response += "{\n";
//    correct_response += "\tsuccess: true\n";
//    correct_response += "\tservice: Upload\n";
//    correct_response += "\tis_uploaded_file_end: true\n";
//    correct_response += "}\n";
//
//    EXPECT_EQ(correct_response, temp_response);
//}
