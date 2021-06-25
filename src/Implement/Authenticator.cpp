// Copyright (c) 2021, 鍾淯丞, 周杰仕, 林仁鴻. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "Authenticator.h"

Authenticator *Authenticator::only_authenticator = nullptr;

Authenticator *Authenticator::GetInstance() {
  if (only_authenticator == nullptr) {
    only_authenticator = new Authenticator();
  }
  return only_authenticator;
}

// not mvp so will only return true for authenticating
bool Authenticator::CheckAccount(const std::string &account,
                                 const std::string &password) {
  return true;
}

// not mvp, may be done after basic function end
std::string Authenticator::SearchAccount(const std::string &account) {
  return "";
}

Authenticator::Authenticator() {}
