// Copyright (c) 2021, 鍾淯丞, 周杰仕, 林仁鴻. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef Group4_Header_MainManager_H_
#define Group4_Header_MainManager_H_

#include <arpa/inet.h>
#include <netinet/in.h>
#include <signal.h>
#include <unistd.h>

#include <string>
#include <unordered_map>
#include <vector>

#include "HttpListener.h"
#include "RequestHandler.h"

// will initialize http listener, do multiprocess when listener callback
class MainManager {
 public:
  // httpListener callback, do fork and new requestHandler to call api, child
  // process add to parents vector for managing.
  void NewRequest(const int &request_fd);
  // requestHandler callback, remove process from parents vector.
  // won't be changed after forked.
  void EndRequest();
  // for managing all processes.
  // socket file descripter => pid_t
  std::unordered_map<int, pid_t> socket_map;
  // get socket_map length
  int GetSize();

  // Initlize singleton instance
  void InitInstance(const uint16_t &port_num);
  // used for unit test, passing mock requestHandler
  void SetRequestHandler(RequestHandler *request_handler);

  // remove process from socket_map by socket
  void RemoveBySocket(const int &socket_num);
  // remove process from socket_map by pid
  void RemoveByPid(const pid_t &p);
  // get process by socket
  pid_t GetProcess(int socket_num);
  // stop listening
  void StopListen();

  // singleton code convention method, listen port number is required.
  static MainManager *GetInstance();

  ~MainManager(void);

  // Delete copy constructor
  MainManager(const MainManager &cpy) = delete;
  // Delete assignment operator
  MainManager &operator=(const MainManager &cpy) = delete;

 protected:
  // singleton code convention method.
  static MainManager *only_mainManager;
  // used to record which port is listening, one process will listen one port
  // will call httpListener.BindPort()
  uint16_t port_num;
  // use request_handler as factory pattern
  RequestHandler *request_handler;
  
 private:
  // singleton code convention method.
  MainManager();
};

#endif
