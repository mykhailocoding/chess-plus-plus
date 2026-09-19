//----------------------------------------------------------------------------------------------------------------------
/// creates the base class for all pieces ( basic pieces special pieces and passive pieces) and excecutes the basic  
/// movements of the pieces and promotes pawns if they reach the backrank of the oppononent as well as stop the game 
/// if a goldenPawn reaches the back rank
//----------------------------------------------------------------------------------------------------------------------


#include "Piece.hpp"
#include "ActivePower.hpp"
#include "Player.hpp"
#include "Board.hpp"
#include "Square.hpp"
#include "Pawn.hpp"
#include "Item.hpp"

Piece::Piece(
    PieceType piece_type,
    std::string id,
    std::size_t value,
    SpecialPowerType special_power_type, std::string short_name) : piece_type_(piece_type),
                                                                   id_(id),
                                                                   owner_(nullptr),
                                                                   short_name_(short_name),
                                                                   value_(value),
                                                                   frozen_counter_(0),
                                                                   invincible_counter_(0),
                                                                   item_(nullptr),
                                                                   special_power_type_(special_power_type),
                                                                   parity_(Parity::NONE),
                                                                   first_move_(true) {}

Piece::Piece(const Piece &piece) : piece_type_(piece.piece_type_),
                                   id_(piece.id_),
                                   short_name_(piece.short_name_),
                                   value_(piece.value_),
                                   coordinates_(piece.coordinates_),
                                   frozen_counter_(piece.frozen_counter_),
                                   invincible_counter_(piece.invincible_counter_),
                                   special_power_type_(piece.special_power_type_),
                                   parity_(piece.parity_),
                                   first_move_(piece.first_move_)
{
  if (piece.owner_ != nullptr)
  {
    owner_ = new Player(*(piece.owner_));
  }
  else
  {
    owner_ = nullptr;
  }

  if (piece.power_ != nullptr)
  {
    power_ = Utils::copyPower(piece.id_, *(piece.power_.get()));
  }
  else
  {
    power_ = nullptr;
  }

  if (piece.item_ != nullptr)
  {
    item_ = std::make_unique<Item>(*(piece.item_.get()));
  }
  else
  {
    item_ = nullptr;
  }
}

Piece::~Piece() = default; 

void Piece::setCoordinates(const Coordinates &new_coords)
{
  this->coordinates_ = new_coords;
}

void Piece::setOwner(Player *owner)
{
  this->owner_ = owner;
  if (owner_ == nullptr)
  {
    return;
  }
  else if (owner->getId() == WHITE_ID)
  {
    // unicode chess symbols take up 3 bytes in memory so the letter is stored at index 3
    short_name_.at(3) = std::toupper(short_name_.at(3));
  }
  else if (owner->getId() == BLACK_ID)
  {
    short_name_.at(3) = std::tolower(short_name_.at(3));
  }
}

void Piece::addItem(std::unique_ptr<Item> item)
{
  // move safely deletes old Item object and creates new one
  item_ = std::move(item);
}

bool Piece::hasInvisibilityCloak() const
{
  if (!hasItem())
  {
    return false;
  }
  if (item_->getId() == ItemId::CLOAK)
  {
    return true;
  }
  return false;
}

bool Piece::hasQueenRepellant() const
{
  if (!hasItem())
  {
    return false;
  }
  if (item_->getId() == ItemId::REPEL)
  {
    return true;
  }
  return false;
}

bool Piece::hasShield() const
{
  if (!hasItem())
  {
    return false;
  }
  if (item_->getId() == ItemId::SHIELD)
  {
    return true;
  }
  return false;
}

bool Piece::checkShield()
{
  if (hasShield())
  {
    item_.reset(); // deleting the unique pointer
    return true;
  }
  return false;
}

bool Piece::hasItem() const
{
  if (item_ != nullptr)
  {
    return true;
  }
  else
  {
    return false;
  }
}

void Piece::removeItem()
{
  item_.reset();
}

std::unique_ptr<Item> Piece::releaseItem()
{
  return std::move(item_);
}

void Piece::setParity(Parity parity)
{
  parity_ = parity;
}

std::string Piece::getFGColor() const
{
  if (owner_ != nullptr && owner_->getId() == WHITE_ID)
  {
    return "\033[1;38;5;247m"; // white player
  }
  else
  {
    return "\033[1;38;5;16m"; // blackPlayer
  }
}

bool Piece::operator==(const Piece &rhs) const
{
  if (this->id_ == rhs.id_)
  {
    return true;
  }
  else
  {
    return false;
  }
}

void Piece::updateCounters()
{
  if (invincible_counter_ > 0)
    invincible_counter_--;
  if (frozen_counter_ > 0)
    frozen_counter_--;
}

bool Piece::canBeCaptured(PieceType type)
{
  if(invincible_counter_ > 0)
  {
    return false;
  }
  if (type == PieceType::Queen && hasQueenRepellant())
  {
    return false;
  }
  return true;
}

bool Piece::canMove(Game *game)
{
  if (invincible_counter_ != 0 || frozen_counter_ != 0)
  {
    return false;
  }
  if (parity_ == Parity::EVEN && game->getCurrentTurn() % 2 != 0)
  {
    return false;
  }
  if (parity_ == Parity::ODD && game->getCurrentTurn() % 2 == 0)
  {
    return false;
  }
  return true;
}

void Piece::reduceFrozenCounter()
{
  if (frozen_counter_ != 0)
  {
    frozen_counter_--;
  }
}

bool Piece::hasSpecialPower()
{
  if (special_power_type_ == SpecialPowerType::Active)
  {
    return true;
  }
  else
  {
    return false;
  }
}

bool Piece::isFrozen()
{
  if (frozen_counter_ == 0)
  {
    return false;
  }
  else
  {
    return true;
  }
}

void Piece::move(Game &game, bool is_capture, Square *target_square, std::optional<char> promote_to)
{
  int source_row = coordinates_.getRank() - 1;
  int source_column = coordinates_.getFile() - 'A';
  int target_row = target_square->getCoordinates().getRank() - 1;
  int target_column = target_square->getCoordinates().getFile() - 'A';

  Player *current_player = game.getBoard().getSquare(source_row, source_column)->getPiece()->getOwner();

  int back_rank_opponent;
  if (current_player->getId() == WHITE_ID)
  {
    back_rank_opponent = 7;
  }
  else if (current_player->getId() == BLACK_ID)
  {
    back_rank_opponent = 0;
  }

  auto self_pointer = game.getBoard().getSquare(source_row, source_column)->releasePiece();
  bool piece_is_pawn;
  if (self_pointer->getType() == PieceType::Pawn)
  {
    piece_is_pawn = true;
  }
  else
  {
    piece_is_pawn = false;
  }

  if (is_capture == true)
  {
    if(game.getBoard().getSquare(target_row, target_column)->hasPiece())
    {
      if(game.getBoard().getSquare(target_row, target_column)->getPiece()->hasItem())
      {
        self_pointer->addItem(game.getBoard().getSquare(target_row, target_column)->getPiece()->releaseItem());
      }
    }
    // execute en pasant and move piece to prison
    if (piece_is_pawn == true && target_square->getPiece() == nullptr)
    {
      //check item for en passant case
      if(game.getBoard().getSquare(source_row, target_column)->hasPiece())
      {
        if(game.getBoard().getSquare(source_row, target_column)->getPiece()->hasItem())
        {
          self_pointer->addItem(game.getBoard().getSquare(source_row, target_column)->getPiece()->releaseItem());
        }
      }
      current_player->addPieceToPrison(game.getBoard().getSquare(source_row, target_column)->releasePiece());
    }
    // move piece into prison
    else 
    {
      current_player->addPieceToPrison(target_square->releasePiece());
    }
  }

  this->coordinates_ = target_square->getCoordinates();
  this->first_move_ = false;
  game.getBoard().getSquare(target_row, target_column)->setPiece(std::move(self_pointer));

  // if pawn at backrank
  if ((piece_is_pawn == true) && (target_row == back_rank_opponent) && (promote_to.has_value()))
  {
    if (this->getId() != "PGLD")
    {
      char promote_to_char = *promote_to;
      Coordinates pawn_position = this->getCoordinates();
      game.promote(game.getBoard(), pawn_position, promote_to_char);
    }
  }
  else if (piece_type_ == PieceType::Pawn && ((target_row != back_rank_opponent && promote_to.has_value()) ||
           (target_row == back_rank_opponent && !promote_to.has_value())))
  {
    throw CustomException(game.getErrorMessages().at(ErrorType::INVALID_MOVE));
  }
}

bool Piece::hasPotion()
{
  if (hasItem() &&
      (item_->getId() == ItemId::FREEZE || item_->getId() == ItemId::TP ||
       item_->getId() == ItemId::EVENODD || item_->getId() == ItemId::LUKE))
  {
    return true;
  }
  else
  {
    return false;
  }
}

bool Piece::isInvincible()
{
  if (invincible_counter_ == 0)
  {
    return false;
  }
  else
  {
    return true;
  }
}
