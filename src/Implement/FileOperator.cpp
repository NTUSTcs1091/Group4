// Copyright (c) 2021, 鍾淯丞, 周杰仕, 林仁鴻. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "FileOperator.h"

#include "DownloadStream.h"
#include "ResponseHandler.h"
#include "UploadStream.h"

int FileOperator::Upload(std::unique_ptr<OperateData> data) {
  // where to upload include fileName
  std::string path = data->body["path"];

  // Binary data that needs to be written
  std::string binary_data = data->body["data"];

  // The file content is end
  bool is_end = (data->body["is_end"] == "true");

  int result_code = UploadStream(path).AppendToFile(binary_data, is_end);
  if (result_code == 1)
    return 200;
  else
    return 500;
}

int FileOperator::Download(std::unique_ptr<OperateData> data,
                           std::string& file_content) {
  try {
    // where to download include fileName
    std::string path = data->body["path"];
    unsigned long pos = 0;
    int result_code =
        DownloadStream(path, 2 * 1024 * 1024).ReadChunk(pos, &file_content);
    if (result_code == 1 || result_code == 2)
      return 200;
    else
      return 500;
  } catch (std::invalid_argument& e) {
    throw e;
  }
}

void FileOperator::CallingAPI(std::unique_ptr<OperateData> data) {
  // Get client file descriptor
  const std::string client_fd = data->header["client_file_descriptor"];
  // GET, POST, PUT, DELETE
  const std::string method = data->header["method"];
  // explorer_file
  const std::string url = data->header["url"];

  // OperatorData for response
  std::unique_ptr<OperateData> response = std::make_unique<OperateData>();
  try {
    // Upload
    if (method == "POST") {
      response->body["is_uploaded_file_end"] = data->body["is_end"];
      response->header["status_code"] = std::to_string(Upload(std::move(data)));
      if (std::stoi(response->header["status_code"]) == 200) {
        response->body["service"] = "Upload";
        response->body["success"] = "true";
      } else {
        throw std::invalid_argument("Something error occurred in POST method.");
      }

      ResponseHandler response_handler;
      // Send to client
      response_handler.Send(client_fd, std::move(response));

    }
    // Download
    else if (method == "GET") {
      std::string file_content = "";
      response->header["status_code"] =
          std::to_string(Download(std::move(data), file_content));

      if (std::stoi(response->header["status_code"]) == 200) {
        response->body["file_content"] = file_content;
        response->body["service"] = "Download";
        response->body["success"] = "true";
      } else {
        throw std::invalid_argument("Something error occurred in GET method.");
      }

      ResponseHandler response_handler;
      // Send to client
      response_handler.Send(client_fd, std::move(response));
    } else {
      throw std::invalid_argument("No method named \"" + method + "\"" +
                                  " in http request methods.");
    }
  } catch (std::invalid_argument& e) {
    response->header["status_code"] = "500";
    response->body["success"] = "false";
    response->body["error_message"] = e.what();
    ResponseHandler response_handler;
    // Send to client
    response_handler.Send(client_fd, std::move(response));
  }
}

FileOperator::FileOperator() {}
