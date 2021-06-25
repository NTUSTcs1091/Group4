// Copyright (c) 2021, 鍾淯丞, 周杰仕, 林仁鴻. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef GROUP4_SRC_HEADER_RESPONSEENCODER_H_
#define GROUP4_SRC_HEADER_RESPONSEENCODER_H_

#include <memory>
#include <string>

#include "OperateData.h"

// Encode the response
class ResponseEncoder {
 public:
  // Singleton code convention method.
  static ResponseEncoder* GetInstance();

  // Encode head and body information
  std::string Encode(const std::unique_ptr<OperateData>& data);

  // Not copyable or movable
  ResponseEncoder(const ResponseEncoder& copy) = delete;
  ResponseEncoder& operator=(const ResponseEncoder& copy) = delete;

 private:
  // Singleton code convention method
  ResponseEncoder();
};

#endif /* GROUP4_SRC_HEADER_RESPONSEENCODER_H_ */
