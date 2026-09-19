//---------------------------------------------------------------------------------------------------------------------
/// Painter rook's special power. Validates target square, moves the rook there, identifies all squares on the path
/// including the starting one, changes their type to the basic square with accoriding earlier identified color.
//---------------------------------------------------------------------------------------------------------------------
#include "PainterRookPower.hpp"
#include "Game.hpp"
#include "Square.hpp"
#include "SpawnSquare.hpp"

PainterRookPower::PainterRookPower() {}

void PainterRookPower::usePower(Game* game, UserInputSpecial& user_input_special)
{
  bool capture = false;
  bool move = false;
  setContext(game, user_input_special);
  setMana(distinguishManaCost());
  auto* targeted_piece = game->getBoard().getSquare(target_square_)->getPiece();
  if(targeted_piece != nullptr)
  {
    if(targeted_piece->getOwner() != game->getCurrentPlayer())
    {
      capture = true;
    }
    else
    {
      throw CustomException(game->getErrorMessages().at(ErrorType::INVALID_MOVE));
      //contains friendly piece
    }
  }
  else
  {
    move = true;
  }
  bool not_enough_mana = false;
  if(!validateMana(game->getCurrentPlayer()->getCurrentMana()))
  {
    not_enough_mana = true;
  }
  Square* square = game->getBoard().getSquare(square_);
  Square* target_square = game->getBoard().getSquare(target_square_);
  if(capture)
  {
    //we check with isMoveValid whether the piece can capture the piece on the target square
    if(square->getPiece()->isMoveValid(game->getBoard(), target_square))
    {
      //because invalid move error has higher priority we first have to check it before throwing mana error
      if(not_enough_mana)
      {
        throw CustomException(game->getErrorMessages().at(ErrorType::INSUFFICIENT_MANA));
      }
      //if the piece on the target square has shield we break it but do not move
      if(target_square->getPiece()->checkShield())
      {
        game->reduceMana(mana_cost_);
        return;//do not paint anything because rook stays on the same square
      }
      //if the piece on the target square has item, we take it before capturing the piece
      if(target_square->getPiece()->hasItem())
      {
        square->getPiece()->addItem(target_square->getPiece()->releaseItem());
      }
      //we capture the piece on the target square
      std::unique_ptr<Piece> captured_piece = target_square->releasePiece();
      game->getCurrentPlayer()->addPieceToPrison(std::move(captured_piece));
      target_square->setPiece(square->releasePiece());
      target_square->getPiece()->setCoordinates(target_square_);
    }
    else
    {
      throw CustomException(game->getErrorMessages().at(ErrorType::INVALID_MOVE));
    }
  }
  else if(move)
  {
    if(square->getPiece()->isMoveValid(game->getBoard(), target_square))
    {
      if(not_enough_mana)
      {
        throw CustomException(game->getErrorMessages().at(ErrorType::INSUFFICIENT_MANA));
      }
      //we check if there is an item on the target square, and if so take it
      if(target_square->getType() == SquareType::SPAWN_SQUARE &&
          dynamic_cast<SpawnSquare*>(target_square)->hasItem())
      {
        square->getPiece()->addItem(dynamic_cast<SpawnSquare*>(target_square)->releaseItem());
      }
      //we move the rook to the target square
      target_square->setPiece(square->releasePiece());
      target_square->getPiece()->setCoordinates(target_square_);
    }
    else
    {
      throw CustomException(game->getErrorMessages().at(ErrorType::INVALID_MOVE));
    }
  }
  identifySquaresToPaint();
  //we temporary remove the piece from the square so we do not delete it with the square
  auto rook = target_square->releasePiece();
  paintSquares(game);
  target_square = game->getBoard().getSquare(target_square_);//we need to update the local variable
  target_square->setPiece(std::move(rook));                 //as we create a new square
  game->reduceMana(mana_cost_);
}


//one difference of the coordinates is always 0 cause rook moves either horisontally or vertically
std::size_t PainterRookPower::distinguishManaCost()
{
  if(target_square_.getFile() == square_.getFile())
  {
    if(target_square_.getRank() > square_.getRank())
    {
      return target_square_.getRank() - square_.getRank();
    }
    else
    {
      return square_.getRank() - target_square_.getRank();
    }
  }
  else
  {
    if(target_square_.getFile() > square_.getFile())
    {
      return target_square_.getFile() - square_.getFile();
    }
    else
    {
      return square_.getFile() - target_square_.getFile();
    }
  }
}

void PainterRookPower::setContext(Game* game, UserInputSpecial& user_input_special)
{
  square_ = user_input_special.square_;
  target_square_ = user_input_special.target_square_;
  identifyColor(game);
}

void PainterRookPower::identifyColor(Game* game)
{
  auto square_type = game->getBoard().getSquare(square_)->getType();
  if(square_type != SquareType::BASIC_WHITE &&
     square_type != SquareType::BASIC_BLACK)
  {
    if(game->getCurrentPlayer()->getId() == WHITE_ID) square_type_new_ = SquareType::BASIC_WHITE;
    if(game->getCurrentPlayer()->getId() == BLACK_ID) square_type_new_ = SquareType::BASIC_BLACK;
  }
  if(square_type == SquareType::BASIC_BLACK) square_type_new_ = SquareType::BASIC_BLACK;
  if(square_type == SquareType::BASIC_WHITE) square_type_new_ = SquareType::BASIC_WHITE;
}

void PainterRookPower::identifySquaresToPaint()
{
  //make the vector empty
  squares_to_paint_.clear();

  if(target_square_.getFile() == square_.getFile())
  {
    if(target_square_.getRank() < square_.getRank())
    {
      for(std::size_t rank = square_.getRank(); rank >= target_square_.getRank(); rank--)
      {
        squares_to_paint_.push_back(Coordinates(target_square_.getFile(), rank));
        if (rank == target_square_.getRank()) break;
      }
    }
    else
    {
      for(std::size_t rank = square_.getRank(); rank <= target_square_.getRank(); rank++)
      {
        squares_to_paint_.push_back(Coordinates(target_square_.getFile(), rank));
        if (rank == target_square_.getRank()) break;
      }
    }
  }
  else
  {
    if(target_square_.getFile() < square_.getFile())
    {
      for(char file = square_.getFile(); file >= target_square_.getFile(); file--)
      {
        squares_to_paint_.push_back(Coordinates(file, target_square_.getRank()));
        if (file == target_square_.getFile()) break;
      }
    }
    else
    {
      for(char file = square_.getFile(); file <= target_square_.getFile(); file++)
      {
        squares_to_paint_.push_back(Coordinates(file, target_square_.getRank()));
        if (file == target_square_.getFile()) break;
      }
    }
  }
}

void PainterRookPower::paintSquares(Game* game)
{
  for(auto& coords : squares_to_paint_)
  {
    game->getBoard().setSquare(coords, square_type_new_);//delete old square, create new one
  }
}
