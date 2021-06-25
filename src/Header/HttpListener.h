// Copyright (c) 2021, 鍾淯丞, 周杰仕, 林仁鴻. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef GROUP4_HEADER_HTTPLISTENER_H_
#define GROUP4_HEADER_HTTPLISTENER_H_

#include <memory.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#include <functional>
#include <thread>

// Listen specific port and will callback MainManager function when receive
// request
class HttpListener {
 public:
  // Init instance, callback should pass client file descriptor
  void InitInstance(std::function<void(const int &fd)> callback,
                    const int &port_num);
  // Singleton code convention, must bind callback for listening port and
  // require listening port
  static HttpListener *GetInstance();
  // bind specific port to listen
  void BindPort(const int &port_num);
  // which contains waiting message and do the callback, called by StartListen
  // with multithread
  void ThreadListen();
  // using multithread to listen
  void StartListen();
  // stop listening and turn off multithread.
  void EndListen();
  // stop listening
  void StopListen();
  ~HttpListener(void);
  // non copyable
  HttpListener(HttpListener &cpy) = delete;
  HttpListener &operator=(const HttpListener &cpy) = delete;

 protected:
  // Singleton code convention
  HttpListener();

 private:
  // will be used when listen port accept connection, throwing file descriptor
  // to new process. listened message must pass through callback.
  std::function<void(const int &)> callback;
  // record client
  int client_fd;
  int server_fd;
  bool start_listen;
  std::thread listen_thread;
  static HttpListener *only_http_listener;
};

#endif
