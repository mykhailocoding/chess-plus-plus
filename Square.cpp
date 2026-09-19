//---------------------------------------------------------------------------------------------------------------------
/// Base class for the squares. Contains constructor, deep copy constructor, default virtual destructor, methods for
/// printing, copy method, and methods for handling of the pieces.
//---------------------------------------------------------------------------------------------------------------------
#include "Square.hpp"

Square::Square(SquareType type, Coordinates coordinates) : type_ (type), piece_(nullptr), coordinates_(coordinates){}

Square::Square(const Square& square) : type_(square.type_), coordinates_(square.coordinates_)
{
  if (square.piece_ != nullptr)
  {
    piece_ = Utils::copyPiece(square.piece_->getId(), *(square.piece_));
  }
  else
  {
    piece_ = nullptr;
  }
}

void Square::print(Game &game)
{
  std::cout << getBackgroundColor();
  std::cout << getItemSymbol(game);

  if(piece_ != nullptr && (!piece_->hasInvisibilityCloak() ||
     piece_->getOwner()->getId() == game.getCurrentPlayer()->getId()))
  {
    //we print the piece
    //if it does not have invisibility cloak
    //if it has invisibility cloak but belongs to the current player
    std::cout << piece_->getFGColor() << std::format("{:<5}", piece_->getShortName());
  }
  else
  {
    std::cout << "   ";
  }
  std::cout << "\033[0m";
}

std::string Square::getItemSymbol(Game &game) const
{
  if(piece_ != nullptr)
  {
    if(piece_->getType() == PieceType::King)
    {
      //check king status
      PlayerStatus player_status = game.checkPlayerStatus(piece_->getOwner());
      switch (player_status)
      {
        case PlayerStatus::CHECK_MATE:
          return "#";
        case PlayerStatus::STALE_MATE:
          return "?";
        case PlayerStatus::CHECK:
          return "!";
        default:
          break;
      }
    }
    //if the piece has item we print it
    //if piece has the cloak we do not print it
    if(piece_->hasInvisibilityCloak() && piece_->getOwner()->getId() == game.getCurrentPlayer()->getId())
    {
      return piece_->getItem()->getDisplayName();
    }
    else if(piece_->hasInvisibilityCloak() && piece_->getOwner()->getId() != game.getCurrentPlayer()->getId())
    {
      return " ";
    }
    //regular item
    if(piece_->hasItem())
    {
      return piece_->getItem()->getDisplayName();
    }
  }
  return " ";
}

std::string Square::getBackgroundColor() const
{
  switch(type_)
  {
    case SquareType::BASIC_WHITE:
      return "\033[48;5;223m";
    case SquareType::BASIC_BLACK:
      return "\033[48;5;94m";
    case SquareType::MANA_SQUARE:
      return "\033[48;5;32m";
    case SquareType::BOOST_SQUARE:
      return "\033[48;5;226m";
    case SquareType::SPAWN_SQUARE:
      return "\033[48;5;28m";
    default:
      return "\033[0m";
  }
}

Piece* Square::getPiece()
{
  return piece_.get();
}

void Square::setPiece(std::unique_ptr<Piece> piece)
{
  piece_ = std::move(piece);
}

Coordinates Square::getCoordinates()
{
  return coordinates_;
}

bool Square::hasPiece()
{
  if (piece_ == nullptr)
  {
    return false;
  }
  else
  {
    return true;
  }
}

std::unique_ptr<Piece> Square::releasePiece()
{
  return std::move(piece_); 
}

bool Square::isSpecialSquare()
{
  if(type_ != SquareType::BASIC_BLACK && type_ != SquareType::BASIC_WHITE)
  {
    return true;
  }
  return false;
}

SquareType Square::getType()
{
  return type_;
}
