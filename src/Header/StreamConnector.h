// Copyright (c) 2021, 鍾淯丞, 周杰仕, 林仁鴻. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef GROUP4_SRC_STREAMCONNECTOR_H_
#define GROUP4_SRC_STREAMCONNECTOR_H_

#include <string>

// File management for client
class StreamConnector {
 public:
  // Constructor
  StreamConnector();

  // Not copyable or movable
  StreamConnector(const StreamConnector &copy) = delete;
  StreamConnector &operator=(const StreamConnector &copy) = delete;

 private:
  // Use to storage data (JSON format)
  std::string data;
  // Use to connect stream
  SocketProcess sock;
};

#endif /* GROUP4_SRC_STREAMCONNECTOR_H_ */
