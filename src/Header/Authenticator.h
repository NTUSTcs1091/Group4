// Copyright (c) 2021, 鍾淯丞, 周杰仕, 林仁鴻. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef GROUP4_HEADER_AUTHENTICATOR_H_
#define GROUP4_HEADER_AUTHENTICATOR_H_

#include <string>

// used to check if request is send from valid user
// when getting request, requesthandler call
// authenticator::CheckAccount(account, password) check if it's valid. if return
// true then keep handle request, false will deny the request.
class Authenticator {
 public:
  // singleton code convention method.
  static Authenticator* GetInstance();
  // check if login is correct
  bool CheckAccount(const std::string& account, const std::string& password);
  // check if account exist
  std::string SearchAccount(const std::string& account);
  // non copyable
  Authenticator(Authenticator& cpy) = delete;
  Authenticator& operator=(Authenticator& cpy) = delete;

 protected:
  static Authenticator* only_authenticator;

 private:
  // singleton code convention method.
  Authenticator();
};

#endif
