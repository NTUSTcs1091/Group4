// Copyright (c) 2021, 鍾淯丞, 周杰仕, 林仁鴻. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "MainManager.h"

MainManager *MainManager::only_mainManager = nullptr;

namespace {
void SigHandle(int sig, siginfo_t *info, void *ctx) {
  if (sig == SIGUSR1) {
    MainManager::GetInstance()->RemoveByPid(info->si_pid);
  }
}
}  // namespace

void MainManager::SetRequestHandler(RequestHandler *request_handler) {
  this->request_handler = request_handler;
}

void MainManager::InitInstance(const uint16_t &port_num) {
  this->port_num = port_num;
  // when child process ends, it'll exit itself and need to notify parent
  // process to remove it from socket_map child process will end with calling
  // EndRequest()
  struct sigaction act;
  act.sa_sigaction = SigHandle;
  sigemptyset(&act.sa_mask);
  act.sa_flags = SA_SIGINFO;
  // SIGUSR1 is used for customized kill command, which will make parent process
  // remove child processfrom socket_map
  sigaction(SIGUSR1, &act, NULL);
  request_handler = new RequestHandler();
  HttpListener *listen_socket = HttpListener::GetInstance();

  listen_socket->InitInstance(
      std::bind(&MainManager::NewRequest, this, std::placeholders::_1),
      port_num);

  listen_socket->StartListen();
}

MainManager *MainManager::GetInstance() {
  if (only_mainManager == nullptr) {
    only_mainManager = new MainManager();
  }
  return only_mainManager;
}

void MainManager::NewRequest(const int &socket_fd) {
  pid_t child_pid = fork();
  // means parent
  if (child_pid > 0) {
    socket_map[socket_fd] = child_pid;
  }
  // means child
  // requestHandler in parent process will never need to handle request, so
  // .SetFd can be used repeatly.
  else if (child_pid == 0) {
    request_handler->SetFd(socket_fd);
    request_handler->WaitForMessage();
  }
  // fork failed
  else {
    // TODO: call error
  }
}

void MainManager::EndRequest() { kill(getppid(), SIGUSR1); }

void MainManager::RemoveBySocket(const int &socket_num) {
  std::unordered_map<int, pid_t>::const_iterator find_process =
      socket_map.find(socket_num);
  if (find_process == socket_map.end()) {
    // TODO: call error
  } else {
    socket_map.erase(find_process);
  }
}

void MainManager::RemoveByPid(const pid_t &p) {
  for (std::unordered_map<int, pid_t>::iterator find_process =
           socket_map.begin();
       find_process != socket_map.end();) {
    if (find_process->second == p) {
      find_process = socket_map.erase(find_process);
    } else {
      ++find_process;
      if (find_process == socket_map.end()) {
        // TODO: call error
      }
    }
  }
}

pid_t MainManager::GetProcess(int socket_num) { return socket_map[socket_num]; }

int MainManager::GetSize() { return socket_map.size(); }

void MainManager::StopListen() { HttpListener::GetInstance()->StopListen(); }

MainManager::MainManager() {}

MainManager::~MainManager(void) { this->StopListen(); }
