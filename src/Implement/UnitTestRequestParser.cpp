#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "OperateData.h"
#include "RequestParser.h"

// test with a sudo string data
TEST(REQUESTPARSER_TEST, ParseString) {
  std::string test_string = "POST /explorer/file HTTP/1.1\n";
  test_string += "Host: echo.paw.cloud\n";
  test_string += "Content-Type: application/json; charset=utf-8\n";
  test_string +=
      "User-Agent: Mozilla/5.0 (Macintosh; Intel Mac OS X 10.12; rv:53.0) "
      "Gecko/20100101 Firefox/53.0\n";
  test_string += "Connection: close\n";
  test_string += "Content-Length: 136\n\n";
  test_string += "{";
  test_string += "\"path\":\"testPath/myFile/filename.txt\",";
  test_string += "\"pos\":\"0\",";
  test_string += "\"data\":\"123456789\"";
  test_string += "}";
  RequestParser* request_parser = RequestParser::GetInstance();
  OperateData* result = request_parser->ParseData(test_string);
  EXPECT_EQ("POST", result->header["method"]);
  EXPECT_EQ("explorer_file", result->header["url"]);
  EXPECT_EQ("testPath/myFile/filename.txt", result->body["path"]);
  EXPECT_EQ("0", result->body["pos"]);
  EXPECT_EQ("123456789", result->body["data"]);
}

int main(int argc, char** argv) {
  testing::InitGoogleMock(&argc, argv);
  RUN_ALL_TESTS();
}