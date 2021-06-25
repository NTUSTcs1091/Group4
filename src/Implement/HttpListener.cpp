// Copyright (c) 2021, 鍾淯丞, 周杰仕, 林仁鴻. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "HttpListener.h"

HttpListener *HttpListener::only_http_listener = nullptr;

void HttpListener::InitInstance(std::function<void(const int &)> callback,
                                const int &port_num) {
  this->callback = callback;
  this->BindPort(port_num);
}

HttpListener *HttpListener::GetInstance() {
  if (only_http_listener == nullptr) {
    only_http_listener = new HttpListener();
  }
  return only_http_listener;
};

void HttpListener::BindPort(const int &port_num) {
  this->server_fd = socket(AF_INET, SOCK_STREAM, 0);
  struct sockaddr_in socket_info;

  if (this->server_fd == -1) {
    // printf("Fail to create a socket.");
    // TODO:
    // Use Logger from other teammate
    return;
  }
  bzero((struct sockaddr *)&socket_info, sizeof(socket_info));
  socket_info.sin_family = PF_INET;
  socket_info.sin_addr.s_addr = INADDR_ANY;
  socket_info.sin_port = htons(port_num);
  bind(this->server_fd, (struct sockaddr *)&socket_info,
       (socklen_t)sizeof(socket_info));
  if(listen(this->server_fd, 1) < 0){
    // std::cout<<"bind port failed"<<std::endl;
  }  
}

void HttpListener::ThreadListen() {
  struct sockaddr_in client_socket_info;
  socklen_t addr_len = sizeof(client_socket_info);
  while (start_listen) {
    this->client_fd = accept(this->server_fd,
                             (struct sockaddr *)&client_socket_info, &addr_len);  
    this->callback(this->client_fd);
  }
}

void HttpListener::StartListen() {
  this->start_listen = true;
  this->listen_thread =
      std::thread(std::bind(&HttpListener::ThreadListen, this));
}

void HttpListener::EndListen() {
  this->start_listen = false;
  this->listen_thread.join();
}

void HttpListener::StopListen(){ 
  shutdown(this->server_fd, SHUT_RDWR); 
  EndListen();
}



HttpListener::HttpListener() { this->start_listen = false; }

HttpListener::~HttpListener(void){ this->StopListen(); }
