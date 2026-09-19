//---------------------------------------------------------------------------------------------------------------------
/// Flipper queen's special power. Validates bounce and target squares, validates path to the target square, moves the
/// queen there/captures the piece on the target square.
//---------------------------------------------------------------------------------------------------------------------
#include "FlipperQueenPower.hpp"
#include "Game.hpp"
#include "Square.hpp"
#include "SpawnSquare.hpp"

FlipperQueenPower::FlipperQueenPower() {}

FlipperQueenPower::FlipperQueenPower(const FlipperQueenPower& power) : ActivePower(power), square_(power.square_),
  target_square_(power.target_square_), bounce_square_(power.bounce_square_) {}

void FlipperQueenPower::usePower(Game* game, UserInputSpecial& user_input_special)
{
  setContext(user_input_special);
  setMana(distinguishManaCost());
  if(wrongBounceSquare())
  {
    throw CustomException(game->getErrorMessages().at(ErrorType::INVALID_MOVE));
  }
  if(wrongTargetSquare())
  {
    throw CustomException(game->getErrorMessages().at(ErrorType::INVALID_MOVE));
  }
  bool capture = false;
  bool move = false;
  if(!validateCaptureAndMove(game, capture, move))
  {
    throw CustomException(game->getErrorMessages().at(ErrorType::INVALID_MOVE));
  }
  bool not_enough_mana = false;
  if(!validateMana(game->getCurrentPlayer()->getCurrentMana()))
  {
    not_enough_mana = true;
  }

  bounceExecution(game, not_enough_mana, capture, move);
  
  game->reduceMana(mana_cost_);
}

void FlipperQueenPower::bounceExecution(Game* game, bool not_enough_mana, bool capture, bool move)
{
  Square* square = game->getBoard().getSquare(square_);
  Square* bounce_square = game->getBoard().getSquare(bounce_square_);
  Square* target_square = game->getBoard().getSquare(target_square_);
  auto rawMove = [&](Square* source_square, Square* target_square, Coordinates target_coords)
  {
    target_square->setPiece(source_square->releasePiece());
    target_square->getPiece()->setCoordinates(target_coords);
  };

  //after validateCaptureAndMove either capture or move is true, or we exit earlier and do not call bounceExecution
  //if the first move(square to bounce square) is incorrect we throw invalid move
  if(!square->getPiece()->isMoveValid(game->getBoard(), bounce_square))
  {
    throw CustomException(game->getErrorMessages().at(ErrorType::INVALID_MOVE));
  }
  //we move queen to the bounce square and check further way
  rawMove(square, bounce_square, bounce_square_);
  if(!bounce_square->getPiece()->isMoveValid(game->getBoard(), target_square))
  {
    rawMove(bounce_square, square, square_);
    throw CustomException(game->getErrorMessages().at(ErrorType::INVALID_MOVE));
  }
  //if there is not enough mana we throw exception and move queen back
  if(not_enough_mana)
  {
    rawMove(bounce_square, square, square_);
    throw CustomException(game->getErrorMessages().at(ErrorType::INSUFFICIENT_MANA));
  }
  
  if(capture)
  {
    //if the piece on the target square has shield we break it but do not move
    if(target_square->getPiece()->checkShield())
    {
      rawMove(bounce_square, square, square_);
      return;
    }
    //if the piece on the target square has item, we take it before capturing the piece
    if(target_square->getPiece()->hasItem())
    {
      bounce_square->getPiece()->addItem(target_square->getPiece()->releaseItem());
    }
    std::unique_ptr<Piece> captured_piece = target_square->releasePiece();
    game->getCurrentPlayer()->addPieceToPrison(std::move(captured_piece));
    rawMove(bounce_square, target_square, target_square_);
  }
  else if(move)
  {
    //we check if there is an item on the target square, and if so take it
    if(target_square->getType() == SquareType::SPAWN_SQUARE &&
        dynamic_cast<SpawnSquare*>(target_square)->hasItem())
    {
      bounce_square->getPiece()->addItem(dynamic_cast<SpawnSquare*>(target_square)->releaseItem());
    }
    rawMove(bounce_square, target_square, target_square_);
  }
}

std::size_t FlipperQueenPower::distinguishManaCost()
{
  //because the movement is diagonal we just have to know difference of the files
  int file_difference = std::abs(target_square_.getFile() - bounce_square_.getFile());
  return file_difference;
}

void FlipperQueenPower::setContext(UserInputSpecial& user_input_special)
{
  square_ = user_input_special.square_;
  target_square_ = user_input_special.target_square_;
  bounce_square_ = user_input_special.bounce_square_;
}

//checks that bounce square is on the boundary and not in the corner
bool FlipperQueenPower::wrongBounceSquare()
{
  char file = bounce_square_.getFile();
  std::size_t rank = bounce_square_.getRank();
  bool on_the_boundary = false;
  if(((file > 'A' && file < 'H') && (rank == 1 || rank == 8)) ||
  ((rank > 1 && rank < 8) && (file == 'A' || file == 'H')))
  {
    on_the_boundary = true;
  }
  else
  {
    on_the_boundary = false;
  }
  std::size_t file_difference = std::abs(bounce_square_.getFile() - square_.getFile());
  std::size_t rank_difference = std::abs(static_cast<int>(bounce_square_.getRank()) - static_cast<int>(square_.getRank()));
  bool diagonal = false;
  if(file_difference != rank_difference)
  {
    diagonal = false;
  }
  else
  {
    diagonal = true;
  }
  return !(diagonal && on_the_boundary);
}

bool FlipperQueenPower::wrongTargetSquare()
{
  if(bounce_square_.getFile() == target_square_.getFile() && bounce_square_.getRank() == target_square_.getRank())
  {
    return true;//target square can not be bounce square(queen has to continue moving)
  }

  //file vector from square to bounce square
  int f1 = bounce_square_.getFile() - square_.getFile();
  //rank vector from square to bounce square
  int r1 = static_cast<int>(bounce_square_.getRank()) - static_cast<int>(square_.getRank());
  //file vector from bounce square to square
  int f2 = target_square_.getFile() - bounce_square_.getFile();
  //rank vector from bounce square to square
  int r2 = static_cast<int>(target_square_.getRank()) - static_cast<int>(bounce_square_.getRank());

  bool diagonal = (std::abs(f2) == std::abs(r2));
  
  char bounce_file = bounce_square_.getFile();
  std::size_t bounce_rank = bounce_square_.getRank();
  bool valid_reflection = false;

  if (bounce_rank == 1 || bounce_rank == 8) 
  {
    //if the bounce axe is horisontal
    //the file vector must remain the same direction
    valid_reflection = ((f1 > 0) == (f2 > 0));
  }
  else if (bounce_file == 'A' || bounce_file == 'H') 
  {
    //if the bounce axe is horisontal
    //the rank vector must remain the same direction
    valid_reflection = ((r1 > 0) == (r2 > 0));
  }
  return !(diagonal && valid_reflection);
}

bool FlipperQueenPower::validateCaptureAndMove(Game* game, bool& capture, bool& move)
{
  auto* targeted_piece = game->getBoard().getSquare(bounce_square_)->getPiece();
  if(targeted_piece != nullptr)
  {
    return false;//if there is a piece it is not a valid path
  }
  targeted_piece = game->getBoard().getSquare(target_square_)->getPiece();
  if(targeted_piece != nullptr)
  {
    if(targeted_piece->getOwner()->getId() == game->getCurrentPlayer()->getId() ||
       !targeted_piece->canBeCaptured(PieceType::Queen))
    {
      return false;
      //if target square contains a friendly piece, or the piece can not be captured
    }
    else
    {
      capture = true;
    }
  }
  else
  {
    move = true;
  }
  return true;
}

void FlipperQueenPower::checkParameters(std::vector<std::string> parameters, UserInputSpecial& user_input_special,
  std::map<ErrorType, std::string>& error_messages)
{
  if ((parameters.at(0).length() != 2) && (parameters.at(1).length() != 2))
  {
    throw CustomException(error_messages.at(ErrorType::INVALID_PARAMETER_SPECIAL_SQUARE));
  }
  else if ((parameters.at(0).at(0) >= 'A') && (parameters.at(0).at(0) <= 'H')
    && (parameters.at(0).at(1) >= '1') && (parameters.at(0).at(1) <= '8')
    && (parameters.at(1).at(0) >= 'A') && (parameters.at(1).at(0) <= 'H')
    && (parameters.at(1).at(1) >= '1') && (parameters.at(1).at(1) <= '8'))
  {
    user_input_special.bounce_square_ = Coordinates(parameters.at(0));
    user_input_special.target_square_ = Coordinates(parameters.at(1));
  }
  else
  {
    throw CustomException(error_messages.at(ErrorType::INVALID_PARAMETER_SPECIAL_SQUARE));
  }
}
