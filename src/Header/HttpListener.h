// Copyright (c) 2021, 鍾淯丞, 周杰仕, 林仁鴻. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef GROUP4_HEADER_HTTPLISTENER_H_
#define GROUP4_HEADER_HTTPLISTENER_H_

#include <memory.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>

#include <function>
#include <thread>

#include "MainManager.h"

class MainManager;

// Listen specific port and will callback MainManager function when receive
// request
class HttpListener {
 public:
  // Init instance
  void InitInstance(
      std::function<void(const int &, const std::string &)> callback,
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
  // non copyable
  HttpListener(HttpListener &cpy) = delete;
  HttpListener &operator=(const HttpListener &cpy) = delete;

 private:
  // Singleton code convention
  HttpListener();
  // will be used when listen port got message, then do callback with file
  // descriptor and message, which will be read to string directly. each
  // listened message must pass through callback.
  std::function<void(const int &, const std::string &)> callback;
  // record client
  int client_fd;
  bool start_listen;
  std::thread listen_thread;
}

#endif
