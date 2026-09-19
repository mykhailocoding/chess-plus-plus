//----------------------------------------------------------------------------------------------------------------------
/// This class is responsible for parsing the user input and calling functions to execute its effect.
//----------------------------------------------------------------------------------------------------------------------

#include "CommandParser.hpp"
#include "Game.hpp"
#include "Square.hpp"
#include "MoveCommand.hpp"
#include "SpecialCommand.hpp"
#include "UseCommand.hpp"
#include "Bishop.hpp"
#include "ConfigParser.hpp"

const std::string CommandParser::USER_INPUT_QUIT_ = "QUIT";

const std::string CommandParser::USER_INPUT_AUTO_ = "AUTO";

const std::string CommandParser::INPUT_PROMPT_ = " > ";

const std::map<std::string, std::function<std::unique_ptr<Command>(Game& game)>> CommandParser::COMMANDS_
{
  {"QUIT", [](Game& game) { return std::make_unique<QuitCommand>(game); }},
  {"BOARD", [](Game& game) { return std::make_unique<BoardCommand>(game); }},
  {"HELP", [](Game& game) { return std::make_unique<HelpCommand>(game); }},
  {"INFO", [](Game& game) { return std::make_unique<InfoCommand>(game); }},
  {"PRISON", [](Game& game) { return std::make_unique<PrisonCommand>(game); }},
  {"SPECIAL", [](Game& game) { return std::make_unique<SpecialCommand>(game); }},
  {"MOVE", [](Game& game) { return std::make_unique<MoveCommand>(game); }},
  {"USE", [](Game& game) { return std::make_unique<UseCommand>(game); }},
  {"PASS", [](Game& game) { return std::make_unique<PassCommand>(game); }},
  {"RESIGN", [](Game& game) { return std::make_unique<ResignCommand>(game); }},
  {"DRAW", [](Game& game) { return std::make_unique<DrawCommand>(game); }},
  {"HISTORY", [](Game& game) { return std::make_unique<HistoryCommand>(game); }}
};

std::string CommandParser::getUserInput(Player* player)
{
  std::cout << "\n" << player->getId() << INPUT_PROMPT_;
  std::string user_input;
  if (!getline(std::cin, user_input))
  {
    execute(USER_INPUT_QUIT_);
    return user_input;
  }
  Utils::trim(user_input);
  Utils::toUpperCase(user_input);
  // if its an invalid quit(invalid parameter count) then its handled in the main command game loop
  // wiht any other input the parameters shouldnt be validated for quit
  if (user_input == USER_INPUT_QUIT_)
  {
    execute(user_input);
  }

  return user_input;
}

void CommandParser::placePiece(Player* player, std::vector<std::unique_ptr<Piece>>& back_rank, Game& game)
{
  std::cout << std::format(PLACING_PIECES_FORMAT_, back_rank.at(0)->getId(),
    game.countPieces(*(back_rank.at(0).get()), back_rank));
  
  while (1)
  {
    try
    {
      std::string user_input = getUserInput(player);
      if (game.getGameState() != GameState::PLAY)
      {
        return;
      }
      if (user_input.length() == 0)
      {
        throw CustomException(game_.getErrorMessages().at(ErrorType::INVALID_PARAMETER_SQUARE));
      }
      std::vector<std::string> tokens;
      Utils::tokenize(user_input, tokens, ' ');
      if (tokens.at(0) == USER_INPUT_QUIT_)
      {
        execute(user_input);
        if (game.getGameState() != GameState::PLAY)
        {
          return;
        }
      }
      else if (tokens.size() != 1)
      {
        throw CustomException(game_.getErrorMessages().at(ErrorType::INVALID_PARAMETER_SQUARE));
      }
      else if (tokens.at(0) == USER_INPUT_AUTO_)
      {
        autoPlacePieces(player, back_rank, game);
        return;
      }
      else if (tokens.at(0).length() == 2)
      {
        Coordinates coordinates;
        if ((tokens.at(0).at(0) >= 'A') && (tokens.at(0).at(0) <= 'H') &&
          (tokens.at(0).at(1) >= '1') && (tokens.at(0).at(1) <= '8'))
        {
          coordinates = Coordinates(tokens.at(0));
        }
        else
        {
          throw CustomException(game_.getErrorMessages().at(ErrorType::INVALID_PARAMETER_SQUARE));
        }
        if(coordinates.validBackRankCoords(player->getId())
          && (!game.getBoard().getSquare(coordinates)->hasPiece()))
        {
          registerPiece(coordinates, player, back_rank, game);
        }
        else
        {
          throw CustomException(game_.getErrorMessages().at(ErrorType::INVALID_PARAMETER_SQUARE));
        }
      }
      else
      {
        throw CustomException(game_.getErrorMessages().at(ErrorType::INVALID_PARAMETER_SQUARE));
      }
    }
    catch(const CustomException& exception)
    {
      std::cout << exception.what() << std::endl;
      continue;
    }
    break;
  }
}

void CommandParser::autoPlacePieces(Player* player, std::vector<std::unique_ptr<Piece>>& back_rank, Game& game)
{
  int rank_index;
  if (player->getId() == WHITE_ID)
  {
    rank_index = 0;
  }
  else
  {
    rank_index = 7;
  }

  for (Square* &square : game.getBoard().getBoard().at(rank_index))
  {
    if (!square->hasPiece())
    {
      registerPiece(square->getCoordinates(), player, back_rank, game);
    }
  }
}

void CommandParser::registerPiece(Coordinates coordinate, Player* player,
  std::vector<std::unique_ptr<Piece>>& back_rank, Game& game)
{
  //place piece on board using coordinates
  back_rank.at(0)->setCoordinates(coordinate);
  back_rank.at(0)->setOwner(player);
  // base class square setPiece used so mana is not increased here
  game.getBoard().getSquare(coordinate)->Square::setPiece(std::move(back_rank.at(0)));
  if (game.getBoard().getSquare(coordinate)->getPiece()->getType() == PieceType::Bishop)
  {
    MovementColor movement_color;
    if (game.getBoard().getSquare(coordinate)->getType() == SquareType::BASIC_WHITE)
    {
      movement_color = MovementColor::WHITE;
    }
    else if (game.getBoard().getSquare(coordinate)->getType() == SquareType::BASIC_BLACK)
    {
      movement_color = MovementColor::BLACK;
    }
    else if (player->getId() == WHITE_ID)
    {
      movement_color = MovementColor::WHITE;
    }
    else
    {
      movement_color = MovementColor::BLACK;
    }
    
    dynamic_cast<Bishop*>(game.getBoard().getSquare(coordinate)->getPiece())->setMovementColor(movement_color);
  }
  back_rank.erase(back_rank.begin(), back_rank.begin() + 1);
}

void CommandParser::execute(std::string input)
{
  Utils::toUpperCase(input);

  std::vector<std::string> parameters;
  Utils::tokenize(input, parameters, ' ');
  std::string command_name = parameters.at(0);
  parameters.erase(parameters.begin(), parameters.begin() + 1); // deletes command name from the vector

  if (COMMANDS_.contains(command_name))
  {
    COMMANDS_.at(command_name)(game_)->execute(parameters);
  }
  else
  {
    throw CustomException(game_.getErrorMessages().at(ErrorType::UNKNOWN_COMMAND)); // catch in game.start()
  }
}
