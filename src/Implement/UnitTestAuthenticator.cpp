#include "Authenticator.h"
#include "gmock/gmock.h"
#include "gtest/gtest.h"

TEST(Authenticator_TEST, SimpleTest) {
  std::string test_name = "test", test_pwd = "test";
  Authenticator *test_target = Authenticator::GetInstance();
  EXPECT_EQ(true, test_target->CheckAccount(test_name, test_pwd));
  EXPECT_EQ("", test_target->SearchAccount(test_name));
}
