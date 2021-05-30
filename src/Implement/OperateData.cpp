// Copyright (c) 2021, 鍾淯丞, 周杰仕, 林仁鴻. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "OperateData.h"

OperateData::OperateData() {}

OperateData::OperateData(OperateData& right) {
  header = right.header;
  body = right.body;
}

std::string& OperateData::operator[](std::string body_key) {
  return body[body_key];
}
