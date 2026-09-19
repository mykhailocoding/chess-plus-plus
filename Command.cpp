//----------------------------------------------------------------------------------------------------------------------
/// This file contains the abstract base for commands and some simple command classes that only use one execute method.
//----------------------------------------------------------------------------------------------------------------------

#include "Command.hpp"
#include "Game.hpp"

const std::map<std::string, std::string> InfoCommand::PIECE_IDS_{
    {"P", "Pawn"},
    {"PGLD", "GoldenPawn"},
    {"PIPT", "ImpatientPawn"},
    {"PSTB", "StubbornnPawn"},
    {"PNRV", "NervousPawn"},
    {"PEXP", "ExplosivePawn"},
    {"R", "Rook"},
    {"RINV", "InvincibleRook"},
    {"RPNT", "PainterRook"},
    {"N", "Knight"},
    {"NJMP", "JumpyKnight"},
    {"NICE", "IceKnight"},
    {"B", "Bishop"},
    {"BCLR", "ColorBlindShop"},
    {"BPRC", "PreacherBishop"},
    {"Q", "Queen"},
    {"QFLP", "FlipperQueen"},
    {"QJMP", "JumpyQueen"},
    {"QHNGR", "HungryQueen"},
    {"K", "King"},
    {"KFRT", "FrightenedKKing"},
    {"KARC", "ArcherKing"}};

const std::map<std::string, PieceShortNameAndManaCost> InfoCommand::SHORT_NAMES_AND_MANA_COST_{
    {"P", {"♟p", 0}},
    {"PGLD", {"♟pg", 0}},
    {"PIPT", {"♟pi", -1}},
    {"PSTB", {"♟p+", 5}},
    {"PNRV", {"♟p-", 1}},
    {"PEXP", {"♟p!", 3}},
    {"R", {"♜r", 0}},
    {"RINV", {"♜ri", -2}},
    {"RPNT", {"♜rp", -1}},
    {"N", {"♞n", 0}},
    {"NJMP", {"♞nj", 0}},
    {"NICE", {"♞ni", 0}},
    {"B", {"♝b", 0}},
    {"BCLR", {"♝bc", 3}},
    {"BPRC", {"♝bp", -1}},
    {"Q", {"♛q", 0}},
    {"QFLP", {"♛qf", -1}},
    {"QJMP", {"♛qj", 2}},
    {"QHNGR", {"♛qh", 0}},
    {"K", {"♚k", 0}},
    {"KFRT", {"♚kf", 0}},
    {"Karc", {"♚ka", -1}}};

Command::Command(Game &game) : game_(game), current_piece_(game.getCurrentPiece()),
  error_messages_(game.getErrorMessages()) {}

void Command::parseCoordinates(std::string coordinate, Coordinates& square)
{
  if (coordinate.length() != 2)
  {
    throw CustomException(error_messages_.at(ErrorType::INVALID_PARAMETER_SQUARE));
  }
  else if ((coordinate.at(0) >= 'A') && (coordinate.at(0) <= 'H')
    && (coordinate.at(1) >= '1') && (coordinate.at(1) <= '8'))
  {
    square = Coordinates(coordinate);
  }
  else
  {
    throw CustomException(error_messages_.at(ErrorType::INVALID_PARAMETER_SQUARE));
  }
}

void QuitCommand::execute(std::vector<std::string> parameters)
{
  if (parameters.size() != 0)
  {
    throw CustomException(error_messages_.at(ErrorType::INVALID_PARAMETER_COUNT));
  }
  else
  {
    game_.setGameState(GameState::QUIT);
  }
}

void BoardCommand::execute(std::vector<std::string> parameters)
{
  if (parameters.size() == 0)
  {
    game_.getBoard().toggleBoard();
    game_.getBoard().printBoard(game_, game_.getWhitePlayer(), game_.getBlackPlayer());
    game_.setPassiveCommand(true);
  }
  else
  {
    throw CustomException(error_messages_.at(ErrorType::INVALID_PARAMETER_COUNT));
  }
  game_.setPassiveCommand(true);
}

void HelpCommand::execute(std::vector<std::string> parameters)
{
  if (parameters.size() == 0)
  {
    game_.setPassiveCommand(true);
    std::cout << "=== Commands ============================================================================\n";
    std::cout << "- help\n";
    std::cout << "    Prints this help text.\n";
    std::cout << "\n";
    std::cout << "- quit\n";
    std::cout << "    Terminates the game.\n";
    std::cout << "\n";
    std::cout << "- board\n";
    std::cout << "    Toggles the board printing.\n";
    std::cout << "\n";
    std::cout << "- info <PIECE_ID>\n";
    std::cout << "    Prints piece information.\n";
    std::cout << "    <PIECE_ID>: The piece ID to be explained.\n";
    std::cout << "\n";
    std::cout << "- history\n";
    std::cout << "    Prints the move history in modified chess notation.\n";
    std::cout << "\n";
    std::cout << "- prison <PLAYER_ID>\n";
    std::cout << "    Lists pieces captured by the specified player.\n";
    std::cout << "    <PLAYER_ID>: [White/Black]\n";
    std::cout << "\n";
    std::cout << "- pass\n";
    std::cout << "    Ends the current player's turn after a move or special ability.\n";
    std::cout << "\n";
    std::cout << "- draw\n";
    std::cout << "    Offers a draw to the opponent.\n";
    std::cout << "\n";
    std::cout << "- resign\n";
    std::cout << "    Resigns the game (loss).\n";
    std::cout << "\n";
    std::cout << "- move <MOVE>\n";
    std::cout << "    Moves a piece using simplified chess notation.\n";
    std::cout << "    <MOVE>: a move in the simplified chess notation format.\n";
    std::cout << "\n";
    std::cout << "- use <SQUARE> [...]\n";
    std::cout << "    Uses a potion.\n";
    std::cout << "    <SQUARE>: The location of the piece, whose potion will be used.\n";
    std::cout << "    [...]: Variable amount of parameters depending on the potion.\n";
    std::cout << "\n";
    std::cout << "- special <SQUARE> [...]\n";
    std::cout << "    Activates a piece's special ability.\n";
    std::cout << "    <SQUARE>: The square where the special piece is located.\n";
    std::cout << "    [...]: Variable parameters depending on the piece (use info for a piece by piece description).\n";
    std::cout << "\n";
    std::cout << "=========================================================================================\n";
  }
  else
  {
    throw CustomException(error_messages_.at(ErrorType::INVALID_PARAMETER_COUNT));
  }
  game_.setPassiveCommand(true);
}

void HistoryCommand::execute(std::vector<std::string> parameters)
{
  if (parameters.size() != 0)
  {
    throw CustomException(error_messages_.at(ErrorType::INVALID_PARAMETER_COUNT));
  }

  game_.printHistory(std::cout);
  game_.setPassiveCommand(true);
}

void PrisonCommand::execute(std::vector<std::string> parameters)
{
  if (parameters.size() != 1)
  {
    throw CustomException(error_messages_.at(ErrorType::INVALID_PARAMETER_COUNT));
  }

  Player *player;

  if (parameters.at(0) == USER_INPUT_WHITE_)
  {
    player = &game_.getWhitePlayer();
  }
  else if (parameters.at(0) == USER_INPUT_BLACK_)
  {
    player = &game_.getBlackPlayer();
  }
  else
  {
    throw CustomException(error_messages_.at(ErrorType::INVALID_PARAMETER_PLAYER));
  }

  game_.setPassiveCommand(true);

  std::cout << game_.getDescriptionMapping().at("BORDER_PRISON") << std::endl;
  std::cout << std::format("{}:", player->getId()) << std::endl;

  // implementing custom bubblesort

  bool is_swap = false;
  std::vector<Piece *> prison; // temporary vector with the raw pointers
  for (auto &piece : player->getPrison())
  {
    prison.push_back(piece.get());
  }

  do
  {
    is_swap = false;

    for (std::size_t piece_index = 1; piece_index < prison.size(); piece_index++)
    {
      if (prison.at(piece_index - 1)->getValue() < prison.at(piece_index)->getValue())
      {
        is_swap = true;
        std::swap(prison.at(piece_index - 1), prison.at(piece_index));
      }
      else if (prison.at(piece_index - 1)->getValue() == prison.at(piece_index)->getValue())
      {
        if (prison.at(piece_index - 1)->getId() > prison.at(piece_index)->getId())
        {
          is_swap = true;
          std::swap(prison.at(piece_index - 1), prison.at(piece_index));
        }
      }
    }
  } while (is_swap);
  //end

  for (std::size_t piece_index = 0; piece_index < prison.size(); piece_index++)
  {
    if (piece_index == 0)
    {
      if (game_.countPieces(*prison.at(piece_index), player->getPrison()) != 1)
      {
        std::cout << std::format("{}x", game_.countPieces(*prison.at(piece_index), player->getPrison()));
      }
      std::cout << prison.at(piece_index)->getId();
    }
    else if (prison.at(piece_index)->getId() == prison.at(piece_index - 1)->getId())
    {
      continue;
    }
    else
    {
      std::cout << ", ";
      if (game_.countPieces(*prison.at(piece_index), player->getPrison()) != 1)
      {
        std::cout << std::format("{}x", game_.countPieces(*prison.at(piece_index), player->getPrison()));
      }
      std::cout << prison.at(piece_index)->getId();
    }
  }

  std::cout << std::endl;
  std::cout << game_.getDescriptionMapping().at("BORDER_D") << std::endl;
}

void InfoCommand::execute(std::vector<std::string> parameters)
{
  if (parameters.size() != 1)
  {
    throw CustomException(error_messages_.at(ErrorType::INVALID_PARAMETER_COUNT));
  }

  std::string user_piece_id = parameters.at(0);
  if (!PIECE_IDS_.contains(user_piece_id))
  {
    throw CustomException(error_messages_.at(ErrorType::INVALID_PARAMETER_PIECE));
  }
  //<D_BORDER_INFO_B>
  std::cout << game_.getDescriptionMapping().at("BORDER_INFO_B") << std::endl;
  //[<PIECE_ID> |
  std::cout << "[" << user_piece_id << " | ";
  // Short name
  PieceShortNameAndManaCost piece_data = SHORT_NAMES_AND_MANA_COST_.at(user_piece_id);
  std::string short_name = piece_data.short_name;
  std::cout << short_name << "] ";
  //<PIECE_NAME>
  std::string piece_name = game_.getPieceIdNameMapping().at(user_piece_id);
  std::cout << piece_name << std::endl;

  int mana_cost = piece_data.mana_cost;
  std::string mana_cost_string = "";
  if (mana_cost != 0)
  {
    if (mana_cost == -1)
    {
      mana_cost_string = "XX";
      std::cout << "Mana: " << mana_cost_string << std::endl;
    }
    else if (mana_cost == -2)
    {
      mana_cost_string = std::to_string(game_.getCurrentTurn());
      std::cout << "Mana: " << mana_cost_string << std::endl;
    }
    else
    {
      if (mana_cost < 10)
      {
        std::cout << std::format("Mana: {:02}", mana_cost) << std::endl;
      }
      else
      {
        std::cout << "Mana: " << mana_cost_string << std::endl;
      }
    }
  }

  // Description: <PIECE_INFO>
  std::cout << "Description: " << game_.getPieceIdInfoMapping().at(user_piece_id) << std::endl;
  // Special: <SPECIAL_SYNTAX>
  if (game_.getPieceIdSyntaxMapping().contains(user_piece_id))
  {
    std::cout << "Special: " << game_.getPieceIdSyntaxMapping().at(user_piece_id) << std::endl;
  }
  else
  {
    std::cout << "Special: None" << std::endl;
  }

  std::cout << game_.getDescriptionMapping().at("BORDER_INFO_E") << std::endl;
  game_.setPassiveCommand(true);
}

void PassCommand::execute(std::vector<std::string> parameters)
{
  if (parameters.size() != 0)
  {
    throw CustomException(error_messages_.at(ErrorType::INVALID_PARAMETER_COUNT));
  }
  else if (game_.getCurrentPiece() == nullptr)
  {
    throw CustomException(error_messages_.at(ErrorType::INVALID_PASS));
  }

  game_.setAdditionalMove(false);
  game_.setPassiveCommand(false);
}

void ResignCommand::execute(std::vector<std::string> parameters)
{
  if (parameters.size() != 0)
  {
    throw CustomException(error_messages_.at(ErrorType::INVALID_PARAMETER_COUNT));
  }
  else if (game_.getCurrentPlayer()->isStaleMated())
  {
    game_.setGameState(GameState::STALEMATE_RESIGNATION_DRAW);
  }
  else if (game_.getCurrentPlayer()->isCheckMated())
  {
    game_.setGameState(GameState::NORMAL_WIN);
    game_.setWinner(&game_.getOpponent());
  }
  else
  {
    game_.setGameState(GameState::RESIGNATION_WIN);
    game_.setWinner(&game_.getOpponent());
  }
}

void DrawCommand::execute(std::vector<std::string> parameters)
{
  if (parameters.size() != 0)
  {
    throw CustomException(error_messages_.at(ErrorType::INVALID_PARAMETER_COUNT));
  }

  std::cout << std::format(PLAYER_OFFERED_DRAW_MESSAGE_,
    game_.getCurrentPlayer()->getId());
  std::string user_input = game_.getCommandParser().getUserInput(&game_.getOpponent());
  if (game_.getGameState() != GameState::PLAY)
  {
    return;
  }

  if (user_input == USER_INPUT_YES_)
  {
    game_.setGameState(GameState::DRAW_COMMAND_DRAW);
  }
  else if (user_input == USER_INPUT_NO_)
  {
    game_.setPassiveCommand(true);
  }
  else
  {
    throw CustomException(error_messages_.at(ErrorType::INVALID_PARAMETER_YES_NO));
  }
}
