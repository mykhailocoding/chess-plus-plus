//----------------------------------------------------------------------------------------------------------------------
/// This class is responsible for validating and executing the effects of the MoveCommand.
//----------------------------------------------------------------------------------------------------------------------

#include "MoveCommand.hpp"
#include "SpawnSquare.hpp"

MoveCommand::MoveCommand(Game &game) : Command(game), is_capture_(false), is_ambiguous_(false) {}

void MoveCommand::execute(std::vector<std::string> parameters)
{
  if (parameters.size() != 1)
  {
    throw CustomException(error_messages_.at(ErrorType::INVALID_PARAMETER_COUNT));
  }

  std::string move = parameters.at(0);
  move_ = move;
  parseParameters(move);

  if (game_.getCurrentPlayer()->isCheckMated() || game_.getCurrentPlayer()->isStaleMated())
  {
    // in the error message ranking invalid move is after invalid parameter move so we have to check this now
    throw CustomException(error_messages_.at(ErrorType::INVALID_MOVE));
  }

  determinePossiblePieces();

  if (possible_pieces_.size() != 1)
  {
    if (current_piece_ != nullptr)
    {
      throw CustomException(error_messages_.at(ErrorType::INVALID_MOVE));
    }
    // ambiguous move
    // move + saving current piece should happen in the function
    is_ambiguous_ = true;
    handleAmbiguousMove();
    return;
  }

  Piece *possible_piece = possible_pieces_.at(0);

  //when castling to a square with a rook standing on target_square the move is still valid 
  bool is_castling = false;
  if (possible_piece->getType() == PieceType::King && game_.getBoard().getSquare(target_square_)->hasPiece())
  {
    if (game_.getBoard().getSquare(target_square_)->getPiece()->getType() == PieceType::Rook)
    {
      is_castling = true;
    }
  }
  if (!is_castling)
  {
    if ((!is_capture_ && game_.getBoard().getSquare(target_square_)->hasPiece()) ||
        ((is_capture_ && !game_.getBoard().getSquare(target_square_)->hasPiece() && piece_type_ != PieceType::Pawn)))
    {
      throw CustomException(error_messages_.at(ErrorType::INVALID_MOVE));
    }
  }

  if ((current_piece_ != nullptr) && (possible_piece != current_piece_))
  {
    throw CustomException(error_messages_.at(ErrorType::INVALID_MOVE));
  }
  else if (Conditions::checkMoveResultInCheck(game_, game_.getBoard().getSquare(target_square_),
    game_.getBoard().getSquare(possible_piece->getCoordinates())))
  {
    throw CustomException(error_messages_.at(ErrorType::INVALID_MOVE));
  }

  // pawn move is valid but at backrank and promotion parameter is empty
  if (possible_piece->getType() == PieceType::Pawn)
  {
    int target_row = target_square_.getRank() - 1;
    if (target_row == 0 || target_row == 7)
    {
      if (!promote_pawn_to_.has_value())
      {
        throw CustomException(error_messages_.at(ErrorType::INVALID_MOVE));
      }
    }
  }

  // the move is valid for sure at this point
  executeMove(possible_piece);
}

void MoveCommand::parseParameters(std::string move)
{
  if (move.length() == 2)
  {
    // pawn move to target square
    parseCoordinates(move, target_square_);
    piece_type_ = PieceType::Pawn;
    is_capture_ = false;
  }
  else if (move.length() == 3)
  {
    // any piece other than pawn moves to target square
    parseMove(move);
  }
  else if (move.length() == 4)
  {
    // either capture or pawn move+promotion
    if (move.at(1) == 'X') // capture
    {
      parseCapture(move);
    }
    else if (move.at(2) == '=') // pawn move+promotion
    {
      parsePawnPromotion(move);
    }
    else
    {
      throw CustomException(error_messages_.at(ErrorType::INVALID_PARAMETER_MOVE));
    }
  }
  else if (move.length() == 6)
  {
    // pawn capture and promotion
    parsePawnCapturePromotion(move);
  }
  else
  {
    throw CustomException(error_messages_.at(ErrorType::INVALID_PARAMETER_MOVE));
  }
}

void MoveCommand::parseCoordinates(std::string coordinate, Coordinates &square)
{
  if ((coordinate.at(0) >= 'A') && (coordinate.at(0) <= 'H') && (coordinate.at(1) >= '1') && (coordinate.at(1) <= '8'))
  {
    square = Coordinates(coordinate);
  }
  else
  {
    throw CustomException(error_messages_.at(ErrorType::INVALID_PARAMETER_MOVE));
  }
}

void MoveCommand::parseMove(std::string move)
{
  switch (move.at(0))
  {
  case 'R':
    piece_type_ = PieceType::Rook;
    break;
  case 'N':
    piece_type_ = PieceType::Knight;
    break;
  case 'B':
    piece_type_ = PieceType::Bishop;
    break;
  case 'Q':
    piece_type_ = PieceType::Queen;
    break;
  case 'K':
    piece_type_ = PieceType::King;
    break;
  default:
    throw CustomException(error_messages_.at(ErrorType::INVALID_PARAMETER_MOVE));
    break;
  }
  move.erase(move.begin());

  parseCoordinates(move, target_square_);
  is_capture_ = false;
}

void MoveCommand::parseCapture(std::string move)
{
  if (move.at(0) == 'B')
  {
    // pawn file specified for capture or bishop piece type specified for capture
    // unknown piece_type and pawn file --> need to check for both options
    possible_pieces_ = Conditions::findPossiblePieces(game_, game_.getCurrentPlayer(), PieceType::Bishop);
    std::vector<Piece *> possible_pawn_pieces = Conditions::findPossiblePieces(game_, game_.getCurrentPlayer(),
      PieceType::Pawn);
    possible_pieces_.insert(possible_pieces_.end(), possible_pawn_pieces.begin(), possible_pawn_pieces.end());
    // piece type is not specified but the pawn file is
    pawn_file_.emplace('B');
    if (possible_pieces_.size() == 0)
    {
      throw CustomException(error_messages_.at(ErrorType::INVALID_MOVE));
    }
  }
  else
  {
    switch (move.at(0))
    {
    case 'R':
      piece_type_ = PieceType::Rook;
      break;
    case 'N':
      piece_type_ = PieceType::Knight;
      break;
    case 'Q':
      piece_type_ = PieceType::Queen;
      break;
    case 'K':
      piece_type_ = PieceType::King;
      break;
    case 'A':
      piece_type_ = PieceType::Pawn;
      pawn_file_.emplace('A');
      break;
    case 'C':
      piece_type_ = PieceType::Pawn;
      pawn_file_.emplace('C');
      break;
    case 'D':
      piece_type_ = PieceType::Pawn;
      pawn_file_.emplace('D');
      break;
    case 'E':
      piece_type_ = PieceType::Pawn;
      pawn_file_.emplace('E');
      break;
    case 'F':
      piece_type_ = PieceType::Pawn;
      pawn_file_.emplace('F');
      break;
    case 'G':
      piece_type_ = PieceType::Pawn;
      pawn_file_.emplace('G');
      break;
    case 'H':
      piece_type_ = PieceType::Pawn;
      pawn_file_.emplace('H');
      break;
    default:
      throw CustomException(error_messages_.at(ErrorType::INVALID_PARAMETER_MOVE));
      break;
    }
  }
  move.erase(move.begin(), move.begin() + 2);

  parseCoordinates(move, target_square_);
  is_capture_ = true;
}

void MoveCommand::parsePawnPromotion(std::string move)
{
  switch (move.at(3))
  {
  case 'R':
    promote_pawn_to_.emplace('R');
    break;
  case 'N':
    promote_pawn_to_.emplace('N');
    break;
  case 'Q':
    promote_pawn_to_.emplace('Q');
    break;
  case 'B':
    promote_pawn_to_.emplace('B');
    break;
  default:
    throw CustomException(error_messages_.at(ErrorType::INVALID_PARAMETER_MOVE));
    break;
  }

  move.erase(move.begin() + 2, move.begin() + 4);

  parseCoordinates(move, target_square_);
  piece_type_ = PieceType::Pawn;
  is_capture_ = false;
}

void MoveCommand::parsePawnCapturePromotion(std::string move)
{
  if ((move.at(1) == 'X') && (move.at(4) == '='))
  {
    piece_type_ = PieceType::Pawn;
    switch (move.at(0))
    {
    case 'A':
      pawn_file_.emplace('A');
      break;
    case 'B':
      pawn_file_.emplace('B');
      break;
    case 'C':
      pawn_file_.emplace('C');
      break;
    case 'D':
      pawn_file_.emplace('D');
      break;
    case 'E':
      pawn_file_.emplace('E');
      break;
    case 'F':
      pawn_file_.emplace('F');
      break;
    case 'G':
      pawn_file_.emplace('G');
      break;
    case 'H':
      pawn_file_.emplace('H');
      break;
    default:
      throw CustomException(error_messages_.at(ErrorType::INVALID_PARAMETER_MOVE));
      break;
    }
    switch (move.at(5))
    {
    case 'R':
      promote_pawn_to_.emplace('R');
      break;
    case 'N':
      promote_pawn_to_.emplace('N');
      break;
    case 'Q':
      promote_pawn_to_.emplace('Q');
      break;
    case 'B':
      promote_pawn_to_.emplace('B');
      break;
    default:
      throw CustomException(error_messages_.at(ErrorType::INVALID_PARAMETER_MOVE));
      break;
    }
    move.erase(move.begin() + 4, move.begin() + 6);
    move.erase(move.begin(), move.begin() + 2);

    parseCoordinates(move, target_square_);
    is_capture_ = true;
  }
  else
  {
    throw CustomException(error_messages_.at(ErrorType::INVALID_PARAMETER_MOVE));
  }
}

void MoveCommand::handleAmbiguousMove()
{
  std::cout << game_.getDescriptionMapping().at("AMBIGUOUS_MOVE") << std::endl;
  std::string user_input = game_.getCommandParser().getUserInput(game_.getCurrentPlayer());
  if (game_.getGameState() != GameState::PLAY)
  {
    return;
  }
  std::vector<std::string> tokens;
  Coordinates coordinates;
  Piece *current_piece = nullptr;

  Utils::tokenize(user_input, tokens, ' ');
  if (tokens.size() != 1)
  {
    throw CustomException(error_messages_.at(ErrorType::INVALID_PARAMETER_SQUARE));
  }
  else if (tokens.at(0) == USER_INPUT_CANCEL_)
  {
    game_.setPassiveCommand(true);
    return;
  }
  else if ((user_input.length() == 2) && (user_input.at(0) >= 'A') && (user_input.at(0) <= 'H') &&
    (user_input.at(1) >= '1') && (user_input.at(1) <= '8'))
  {
    coordinates = Coordinates(user_input);
  }
  else
  {
    throw CustomException(error_messages_.at(ErrorType::INVALID_PARAMETER_SQUARE));
  }

  for (auto &piece : possible_pieces_)
  {
    if (piece->getCoordinates() == coordinates)
    {
      current_piece = piece;
      break;
    }
  }

  if ((current_piece == nullptr) ||
    !current_piece->isMoveValid(game_.getBoard(), game_.getBoard().getSquare(target_square_)) ||
    Conditions::checkMoveResultInCheck(game_, game_.getBoard().getSquare(target_square_),
      game_.getBoard().getSquare(possible_pieces_.at(0)->getCoordinates())))
  {
    throw CustomException(error_messages_.at(ErrorType::INVALID_MOVE));
  }
  else
  {
    executeMove(current_piece);
  }
}

void MoveCommand::updateHistory()
{
  std::string current_move;
  if (is_ambiguous_) // move was ambiguous
  {
    current_move = std::format(AMBIGUOUS_HISTORY_FORMAT_,
      static_cast<char>(tolower(current_piece_->getCoordinates().getFile())),
      current_piece_->getCoordinates().getRank());
  }

  Utils::toLowerCase(move_);
  current_move += move_;

  // if the size of the outer history vector is equal to the turn count then its not the players first move in the round
  if (game_.getCurrentPlayer()->getHistory().size() != game_.getCurrentTurn())
  {
    game_.getCurrentPlayer()->getHistory().resize(game_.getCurrentTurn());
  }
  game_.getCurrentPlayer()->getHistory().at(game_.getCurrentTurn() - 1).push_back(current_move);
}

void MoveCommand::determinePossiblePieces()
{
  if (possible_pieces_.size() == 0) // if piece_type_ was ambiguous the vector is already filled
  {
    possible_pieces_ = Conditions::findPossiblePieces(game_, game_.getCurrentPlayer(), piece_type_);
  }

  for (int piece_counter = possible_pieces_.size(); piece_counter > 0; piece_counter--)
  {
    int piece_index = piece_counter - 1;
    // if the piece cannot perform a valid move to the square its deleted from the possible pieces
    if (!possible_pieces_.at(piece_index)->isMoveValid(game_.getBoard(), game_.getBoard().getSquare(target_square_)))
    {
      possible_pieces_.erase(possible_pieces_.begin() + piece_index);
    }
    else if ( possible_pieces_.at(piece_index)->getType() == PieceType::Pawn)
    {
      if (is_capture_) // pawn capture
      {
        if (pawn_file_.value() != possible_pieces_.at(piece_index)->getCoordinates().getFile())
        {
          possible_pieces_.erase(possible_pieces_.begin() + piece_index);
        }
      }
      else
      {
        // pawn can not move diagonally if is_capture_ is false
        if (possible_pieces_.at(piece_index)->getCoordinates().getFile() != target_square_.getFile())
        {
          possible_pieces_.erase(possible_pieces_.begin() + piece_index);
        }
      }
    }
  }

  if (possible_pieces_.size() == 0)
  {
    throw CustomException(error_messages_.at(ErrorType::INVALID_MOVE));
  }
}

void MoveCommand::executeMove(Piece* piece)
{
  if (game_.getBoard().getSquare(target_square_)->hasPiece())
  {
    // if attacked piece had shield, it will be destroyed in checkShield function
    // we still have to write the move to history, but the attacking piece does not move
    Piece *attacked_piece = game_.getBoard().getSquare(target_square_)->getPiece();
    if (is_capture_ && attacked_piece->checkShield())
    {
      game_.setCurrentPiece(piece);
      current_piece_ = piece;
      updateHistory();
      game_.setPassiveCommand(false);
      return;
    }
  }
  if (game_.getBoard().getSquare(target_square_)->getType() == SquareType::BOOST_SQUARE)
  {
    game_.setAdditionalMove(true);
  }
  else
  {
    game_.setAdditionalMove(false);
  }
  piece->move(game_, is_capture_, game_.getBoard().getSquare(target_square_), promote_pawn_to_);

  // checking if there is an item on the square and adding it to the piece
  // items can be only on spawn squares
  Square *target_square = game_.getBoard().getSquare(target_square_);
  if (target_square->getType() == SquareType::SPAWN_SQUARE &&
      dynamic_cast<SpawnSquare *>(target_square)->hasItem())
  {
    piece->addItem(dynamic_cast<SpawnSquare *>(target_square)->releaseItem());
  }
  game_.setCurrentPiece(piece);
  current_piece_ = piece;
  updateHistory();
  game_.setPassiveCommand(false);
}
