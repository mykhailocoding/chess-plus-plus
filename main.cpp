//----------------------------------------------------------------------------------------------------------------------
/// This file contains the main function of the program which handles initialisation and starts the program.
//----------------------------------------------------------------------------------------------------------------------

#include "Exceptions.hpp"
#include "ConfigParser.hpp"
#include "Game.hpp"

#include <iostream>

const std::size_t VALID_PARAMETER_COUNT = 3;

const std::string WRONG_PARAMETER_COUNT_MESSAGE = "Error: Wrong number of arguments!";
const std::string MEMORY_ALLOCATION_FAILURE_MESSAGE = "Error: Not enough memory!";

enum ReturnValue
{
  SUCCESS,
  MEMORY_ALLOCATION_FAILURE,
  WRONG_PARAMETER_COUNT,
  INVALID_FILE
};

//----------------------------------------------------------------------------------------------------------------------
/// @brief This function is the main function of the program which handles initialisation and starts the program.
/// @param argc number of command line arguments
/// @param argv vector that contains the command line arguments
/// @return Return value of the program which corresponds to the cause of termination.
int main(int argc, char *argv[])
{
  if (argc != VALID_PARAMETER_COUNT)
  {
    std::cout << WRONG_PARAMETER_COUNT_MESSAGE << std::endl;
    return WRONG_PARAMETER_COUNT;
  }

  ConfigParser config_parser;
  std::string game_config_file_path = argv[1];
  std::string message_config_file_path = argv[2];

  try
  {
    config_parser.loadConfigFiles(game_config_file_path, message_config_file_path);

    Game game(config_parser);
    game.start();
    game.endGame();
  }
  catch (const std::bad_alloc& exception)
  {
    std::cout << MEMORY_ALLOCATION_FAILURE_MESSAGE << std::endl;
    return MEMORY_ALLOCATION_FAILURE;
  }
  catch (const InvalidFile& exception)
  {
    std::cout << exception.what() << std::endl;
    return INVALID_FILE;
  }

  return SUCCESS;
}
