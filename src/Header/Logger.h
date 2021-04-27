// Copyright (c) 2021, 鍾淯丞, 周杰仕, 林仁鴻. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef GROUP4_SRC_LOGGER_H_
#define GROUP4_SRC_LOGGER_H_

#include <string>
#include <memory>
#include "OperatorData.h"

// Write operation and result log
class Logger
{
public:
    // Singleton code convention method
    static Logger* GetInstance();
    
    // Write data and warning message
    void WriteLog(const OperatorData &data, const Level &level) const;
    
    // Not copyable or movable
    Logger(const Logger &copy) = delete;
    Logger& operator = (const Logger &copy) = delete;

private:
    // Singleton code convention method
    Logger();
};

#endif /* GROUP4_SRC_LOGGER_H_ */
