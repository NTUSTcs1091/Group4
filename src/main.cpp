// Copyright (c) 2021, 鍾淯丞, 周杰仕, 林仁鴻. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include <iostream>

#include "MainManager.h"

int main() {
  int server_port = 9000;
  MainManager* manager = MainManager::GetInstance();
  manager->InitInstance(server_port);
  std::string command;
  while (true) {
    std::cin >> command;
  }

  return 0;
}
