#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "RequestParser.h"



TEST_F(REQUESTPARSER_TEST, ParseString)
{
    std::string test_string = "POST /explorer/file HTTP/1.1\n" +
                                "Host: echo.paw.cloud\n" +
                                "Content-Type: application/json; charset=utf-8\n" +
                                "User-Agent: Mozilla/5.0 (Macintosh; Intel Mac OS X 10.12; rv:53.0) Gecko/20100101 Firefox/53.0\n" +
                                "Connection: close\n" +
                                "Content-Length: 136\n\n" +
                                "{\n" +
                                '"' + "path" + '"' + ':' + '"' + "testPath/myFile/filename.txt" + '"' + "," + 
                                '"' + "pos" + '"' + ':' + "0" + "," +
                                '"' + "data" + '"' + ':' + "123456789" +
                                "}"
    RequestParser *request_parser = RequestParser::GetInstance();
    OperateData result = request_parser.ParseData(test_string);
    EXPECT_EQ("POST", result.header["method"]);
    EXPECT_EQ("explorer_file", result.header["url"]);
    EXPECT_EQ("testPath/myFile/filename.txt", result.body["path"]);
    EXPECT_EQ("0", result.body["pos"]);
    EXPECT_EQ("123456789", result.body["data"]);
}

int main(int argc, char **argv)
{
    testing::InitGoogleMock(&argc, argv);
    RUN_ALL_TESTS();
}