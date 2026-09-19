//----------------------------------------------------------------------------------------------------------------------
/// This file contains the custom exceptions used throughout the program.
//----------------------------------------------------------------------------------------------------------------------

#include "Exceptions.hpp"

CustomException::CustomException(const std::string& message) : message_(std::format(ERROR_MESSAGE_FORMAT_, message)) {}

const char* CustomException::what() const noexcept
{
  return message_.c_str();
}

InvalidFile::InvalidFile(const std::string& file_path) : message_(std::format(INVALID_FILE_FORMAT_, file_path)) {}

const char* InvalidFile::what() const noexcept
{
  return message_.c_str();
}
