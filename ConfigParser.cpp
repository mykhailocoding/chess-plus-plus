//----------------------------------------------------------------------------------------------------------------------
/// This class is responsible for parsing the provided config files.
//----------------------------------------------------------------------------------------------------------------------

#include "ConfigParser.hpp"
#include "Coordinates.hpp"
#include "Pawn.hpp"
#include "GoldenPawn.hpp"
#include "ImpatientPawn.hpp"
#include "StubbornPawn.hpp"
#include "NervousPawn.hpp"
#include "ExplosivePawn.hpp"
#include "Rook.hpp"
#include "InvincibleRook.hpp"
#include "PainterRook.hpp"
#include "Knight.hpp"
#include "JumpyKnight.hpp"
#include "IceKnight.hpp"
#include "Bishop.hpp"
#include "ColorBlindBishop.hpp"
#include "PreacherBishop.hpp"
#include "Queen.hpp"
#include "FlipperQueen.hpp"
#include "JumpyQueen.hpp"
#include "HungryQueen.hpp"
#include "King.hpp"
#include "FrightenedKing.hpp"
#include "ArcherKing.hpp"
#include "FreezePotion.hpp"
#include "TeleportPotion.hpp"
#include "EvenOddPotion.hpp"
#include "SkywalkerPotion.hpp"
#include "Shield.hpp"
#include "InvisibilityCloak.hpp"
#include "QueenRepellant.hpp"
#include "ManaSquare.hpp"
#include "SpawnSquare.hpp"
#include "BoostSquare.hpp"
#include "ManaSquare.hpp"
#include "SpawnSquare.hpp"
#include "BoostSquare.hpp"

const std::string ConfigParser::MAGIC_NUMBER_GAME_CONFIG_ = "GAME";
const std::string ConfigParser::MAGIC_NUMBER_MESSAGE_CONFIG_ = "MESSAGE";

void ConfigParser::loadConfigFiles(std::string &game_config_file_path, std::string &message_config_file_path)
{
  std::fstream game_config(game_config_file_path);
  std::fstream message_config(message_config_file_path);

  if (!game_config.is_open())
  {
    throw InvalidFile(game_config_file_path);
  }
  else if (!message_config.is_open())
  {
    throw InvalidFile(message_config_file_path);
  }

  std::string magic_number_game;
  std::string magic_number_message;

  std::getline(game_config, magic_number_game);
  std::getline(message_config, magic_number_message);

  if (magic_number_game != MAGIC_NUMBER_GAME_CONFIG_)
  {
    throw InvalidFile(game_config_file_path);
  }
  else if (magic_number_message != MAGIC_NUMBER_MESSAGE_CONFIG_)
  {
    throw InvalidFile(message_config_file_path);
  }

  loadGameConfig(game_config);
  loadMessageConfig(message_config);
}

void ConfigParser::loadGameConfig(std::fstream &game_config)
{
  std::string line;

  while (getline(game_config, line))
  {
    Utils::trim(line);

    if (line.length() == 0)
    {
      continue;
    }

    std::vector<std::string> tokens;
    Utils::tokenize(line, tokens, ' ');

    if (tokens.at(0) == "turns:")
    {
      Utils::stringToSizeT(tokens.at(1), max_turn_count_);
      std::getline(game_config, line);

      // get info of mana from the next line
      std::vector<std::string> mana_config;
      Utils::tokenize(line, tokens, ' ');
      Utils::tokenize(tokens.at(1), mana_config, '/');
      Utils::stringToSizeT(mana_config.at(0), initial_mana_);
      Utils::stringToSizeT(mana_config.at(1), mana_pool_);
    }
    else if (tokens.at(0) == WHITE_ID)
    {
      tokens.at(3).pop_back();
      Utils::stringToSizeT(tokens.at(3), white_elo_score_);
      parsePieces(game_config, white_pieces_);
    }
    else if (tokens.at(0) == BLACK_ID)
    {
      tokens.at(3).pop_back();
      Utils::stringToSizeT(tokens.at(3), black_elo_score_);
      parsePieces(game_config, black_pieces_);
    }
    else if (tokens.at(0) == "Squares")
    {
      parseSquares(game_config);
    }
  }
}

void ConfigParser::loadMessageConfig(std::fstream &message_config)
{
  std::string line;
  std::map<std::string, std::string> error_id_message_mapping;

  while (getline(message_config, line))
  {
    Utils::trim(line);

    if ((line.length() == 0) || (line == MAGIC_NUMBER_MESSAGE_CONFIG_))
    {
      continue;
    }

    std::vector<std::string> tokens;
    Utils::tokenizeWithoutTrimming(line, tokens, ':');

    if (tokens.at(0).starts_with("E"))
    {
      tokens.at(0).erase(0, 2);
      error_id_message_mapping.emplace(tokens.at(0), tokens.at(1));
    }
    else if (tokens.at(0).starts_with("D_N"))
    {
      tokens.at(0).erase(0, 4);
      piece_id_name_mapping_.emplace(tokens.at(0), tokens.at(1));
    }
    else if (tokens.at(0).starts_with("D_I"))
    {
      tokens.at(0).erase(0, 4);
      piece_id_info_mapping_.emplace(tokens.at(0), tokens.at(1));
    }
    else if (tokens.at(0).starts_with("D_S"))
    {
      tokens.at(0).erase(0, 4);
      piece_id_syntax_mapping_.emplace(tokens.at(0), tokens.at(1));
    }
    else
    {
      tokens.at(0).erase(0, 2);
      description_id_message_mapping_.emplace(tokens.at(0), tokens.at(1));
    }
  }
  registerErrorMessages(error_id_message_mapping);
}

void ConfigParser::parsePieces(std::fstream &game_config, std::array<std::vector<std::unique_ptr<Piece>>, 2> &pieces)
{
  std::string line;
  std::vector<std::string> tokens;

  std::getline(game_config, line); // line with nothing but a {
  for (int rank_index = 0; rank_index < 2; rank_index++)
  {
    std::getline(game_config, line);
    Utils::tokenize(line, tokens, ',');
    for (std::string piece_id : tokens)
    {
      std::vector<std::string> piece_constructor;
      Utils::tokenize(piece_id, piece_constructor, 'x');
      if (piece_constructor.size() == 1)
      {
        pieces.at(rank_index).push_back(Utils::createPiece(piece_constructor.at(0)));
      }
      else
      {
        int piece_quantity;
        Utils::stringToInt(piece_constructor.at(0), piece_quantity);
        for (int piece_counter = 0; piece_counter < piece_quantity; piece_counter++)
        {
          pieces.at(rank_index).push_back(Utils::createPiece(piece_constructor.at(1)));
        }
      }
    }
  }
}

void ConfigParser::parseSquares(std::fstream &game_config)
{
  std::string line;
  std::vector<std::string> tokens;
  Square *square;

  std::getline(game_config, line); // line with nothing but a {
  for (std::getline(game_config, line); line != "}"; std::getline(game_config, line))
  {
    Utils::trim(line);
    if (line.length() == 0)
    {
      continue;
    }

    line.pop_back(); // remove : from the end
    Coordinates coordinates(line);
    std::getline(game_config, line);

    Utils::tokenize(line, tokens, ' ');
    tokens.at(2); // id of the square
    if (tokens.at(2) == "SPAWN")
    {
      SpawnSquare* spawn_square = new SpawnSquare(coordinates);
      
      std::vector<std::unique_ptr<Item>> items_;

      std::getline(game_config, line); // list of items stored on the square
      Utils::trim(line);
      line.erase(0, 8); // delete "- list:" from the string
      Utils::tokenize(line, tokens, ',');
      for (std::string item_id : tokens)
      {
        std::vector<std::string> item_constructor;
        Utils::tokenize(item_id, item_constructor, 'x');
        if (item_constructor.size() == 1)
        {
          items_.push_back(Utils::createItem(item_constructor.at(0)));
        }
        else
        {
          int item_quantity;
          Utils::stringToInt(item_constructor.at(0), item_quantity);
          for (int item_counter = 0; item_counter < item_quantity; item_counter++)
          {
            items_.push_back(Utils::createItem(item_constructor.at(1)));
          }
        }
      }

      spawn_square->setItems(items_);
      square = spawn_square;
    }
    else if (tokens.at(2) == "MANA")
    {
      square = new ManaSquare(coordinates);
    }
    else
    {
      square = new BoostSquare(coordinates);
    }

    for (std::vector<Square *> &rank : board_.getBoard())
    {
      for (Square *&square_in_rank : rank)
      {
        if (square_in_rank->getCoordinates() == coordinates)
        {
          delete square_in_rank;
          square_in_rank = square;
        }
      }
    }
  }
}

void ConfigParser::registerErrorMessages(std::map<std::string, std::string>& error_message_mapping)
{
  error_messages_.emplace(ErrorType::UNKNOWN_COMMAND,
    error_message_mapping.at("UNKNOWN_COMMAND"));
  error_messages_.emplace(ErrorType::INVALID_PARAMETER_COUNT,
    error_message_mapping.at("INVALID_PARAM_COUNT"));
  error_messages_.emplace(ErrorType::SPECIAL_USE_UNAVAILABLE,
    error_message_mapping.at("SPECIAL_USE_UNAVAILABLE"));
  error_messages_.emplace(ErrorType::INVALID_PARAMETER_PLAYER,
    error_message_mapping.at("INV_PARAM_PLAYER"));
  error_messages_.emplace(ErrorType::INVALID_PARAMETER_SQUARE,
    error_message_mapping.at("INV_PARAM_SQUARE"));
  error_messages_.emplace(ErrorType::INVALID_PARAMETER_PIECE,
    error_message_mapping.at("INV_PARAM_PIECE"));
  error_messages_.emplace(ErrorType::PLAYER_PIECE_NOT_FOUND,
    error_message_mapping.at("PLAYER_PIECE_NOT_FOUND"));
  error_messages_.emplace(ErrorType::NO_SPECIAL_POWER,
    error_message_mapping.at("NO_SPECIAL_POWER"));
  error_messages_.emplace(ErrorType::INVALID_PARAMETER_COUNT_SPECIAL,
    error_message_mapping.at("INVALID_PARAM_COUNT_SPECIAL"));
  error_messages_.emplace(ErrorType::PIECE_FROZEN,
    error_message_mapping.at("PIECE_FROZEN"));
  error_messages_.emplace(ErrorType::INVALID_PARAMETER_SPECIAL_SQUARE,
    error_message_mapping.at("INV_PARAM_SPECIAL_SQUARE"));
  error_messages_.emplace(ErrorType::INVALID_PARAMETER_PIECE_TYPE,
    error_message_mapping.at("INV_PARAM_PIECE_TYPE"));
  error_messages_.emplace(ErrorType::INVALID_PARAMETER_TURN_COUNT,
    error_message_mapping.at("INV_PARAM_TURN_COUNT"));
  error_messages_.emplace(ErrorType::UNWAVERING_FAITH,
    error_message_mapping.at("UNWAVERING_FAITH"));
  error_messages_.emplace(ErrorType::INVALID_ARCHER_TARGET,
    error_message_mapping.at("INVALID_ARCHER_TARGET"));
  error_messages_.emplace(ErrorType::OPPONENT_PIECE_NOT_FOUND,
    error_message_mapping.at("OPPONENT_PIECE_NOT_FOUND"));
  error_messages_.emplace(ErrorType::INVALID_PARAMETER_MOVE,
    error_message_mapping.at("INV_PARAM_MOVE"));
  error_messages_.emplace(ErrorType::INVALID_MOVE,
    error_message_mapping.at("INVALID_MOVE"));
  error_messages_.emplace(ErrorType::INSUFFICIENT_MANA,
    error_message_mapping.at("INSUFFICIENT_MANA"));
  error_messages_.emplace(ErrorType::NO_POTION_FOUND,
    error_message_mapping.at("NO_POTION_FOUND"));
  error_messages_.emplace(ErrorType::INVALID_PARAMETER_COUNT_USE,
    error_message_mapping.at("INVALID_PARAM_COUNT_USE"));
  error_messages_.emplace(ErrorType::INVALID_PARAMETER_USE,
    error_message_mapping.at("INV_PARAM_USE"));
  error_messages_.emplace(ErrorType::INVALID_PASS,
    error_message_mapping.at("INVALID_PASS"));
  error_messages_.emplace(ErrorType::INVALID_PARAMETER_YES_NO,
    error_message_mapping.at("INV_PARAM_YES_NO"));
  error_messages_.emplace(ErrorType::INVALID_PATH,
    error_message_mapping.at("INVALID_PATH"));
}
