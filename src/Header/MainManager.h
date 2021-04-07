// Copyright (c) 2021, 鍾淯丞, 周杰仕, 林仁鴻. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef Group4_Header_MainManager_H_
#define Group4_Header_MainManager_H_

#include <netinet/in.h>

#include <vector>
#include <unordered_map>

#include "HttpListener.h"
#include "RequestHandler.h"

//will initialize http listener, do multiprocess when listener callback
class MainManager
{
public:
    //httpListener callback, do fork and new requestHandler to call api, child process add to parents vector for managing.
    void NewRequest(const string &request_str);
    //requestHandler callback, remove process from parents vector.
    void EndRequest();
    //for managing all processes.
    //socket file descripter => pid_t
    std::unordered_map<int, pid_t> socket_map;

    //Initlize singleton instance
    void InitInstance(const uint16_t &port_num);
    //singleton code convention method, listen port number is required.
    static MainManager* GetInstance();

    //Delete copy constructor
    MainManager(const MainManager &cpy) = delete;
    //Delete assignment operator
    MainManager& operator=(const MainManager &cpy) = delete;
private:
    //singleton code convention method.
    MainManager();
    //used to record which port is listening, one process will listen one port
    //will call httpListener.BindPort()
    uint16_t port_num;
};

#endif
