//----------------------------------------------------------------------------------------------------------------------
/// This file contains the custom exceptions used throughout the program.
//----------------------------------------------------------------------------------------------------------------------

#ifndef EXCEPTIONS_HPP
#define EXCEPTIONS_HPP

#include <string>
#include <format>
#include <string_view>

class CustomException : public std::exception
{
  private:
    // using std::string_view so the string can be formatted AND declared as a constant
    static constexpr std::string_view ERROR_MESSAGE_FORMAT_ = "[ERROR] {}";

    std::string message_;

  public:
    //------------------------------------------------------------------------------------------------------------------
    /// @brief Constructor that creates a CustomException object and initializes its member variables.
    /// @param message error message that needs to be printed when the exception is caught and its what method is called
    CustomException(const std::string& message);

    //------------------------------------------------------------------------------------------------------------------
    /// @brief Copy constructor is deleted explicitly.
    CustomException(const CustomException&) = delete;

    //------------------------------------------------------------------------------------------------------------------
    /// @brief Destructor is declared explicitly as a default destructor.
    ~CustomException() = default;

    //------------------------------------------------------------------------------------------------------------------
    /// @brief This function overrides the what() method of exceptions to print a custom error message.
    /// @return custom error message formatted correctly
    const char* what() const noexcept override;
};

class InvalidFile : public std::exception
{
  private:
    static constexpr std::string_view INVALID_FILE_FORMAT_ = "Error: Invalid file ({})!";

    std::string message_;

  public:
    //------------------------------------------------------------------------------------------------------------------
    /// @brief Constructor that creates an InvalidFile CustomException object and initializes its member variables.
    /// @param file_path faulty file path read from the command line
    InvalidFile(const std::string& file_path);

    //------------------------------------------------------------------------------------------------------------------
    /// @brief Copy constructor is deleted explicitly.
    InvalidFile(const InvalidFile&) = delete;

    //------------------------------------------------------------------------------------------------------------------
    /// @brief Destructor is declared explicitly as a default destructor.
    ~InvalidFile() = default;

    //------------------------------------------------------------------------------------------------------------------
    /// @brief This function overrides the what() method of exceptions to print a custom error message.
    /// @return custom error message formatted correctly
    const char* what() const noexcept override;
};

#endif
