//---------------------------------------------------------------------------------------------------------------------
/// Implements spawn square. Contains a vector of unique pointers of items, spawns the item according to the logic
/// by copying the item from the vector.
//---------------------------------------------------------------------------------------------------------------------
#include "SpawnSquare.hpp"
#include "Item.hpp"
#include "Piece.hpp"
#include "Utils.hpp"

SpawnSquare::SpawnSquare(Coordinates coordinates): Square(SquareType::SPAWN_SQUARE, coordinates), next_item_index_ (0),
 current_item_on_square_(nullptr) {}

SpawnSquare::SpawnSquare(const SpawnSquare& square) : Square(square), next_item_index_(square.next_item_index_)
{
  if (square.items_.size() != 0)
  {
    for (auto& item : square.items_)
    {
      items_.push_back(Utils::copyItem(item->getId(), *item));
    }
  }

  if (square.current_item_on_square_ != nullptr)
  {
    current_item_on_square_ = Utils::copyItem(square.current_item_on_square_->getId(), *(square.current_item_on_square_));
  }
  else
  {
    current_item_on_square_ = nullptr;
  }
}

std::string SpawnSquare::getItemSymbol(Game &game) const
{
  if(piece_ != nullptr)
  {
    //we substitute the item sign in case king is in check, checkmate, stalemate
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
  }//in spawn square there could be an item on the square so we add logic for this
  if(current_item_on_square_ != nullptr)
  {
    return current_item_on_square_->getDisplayName();
  }
  return " ";
}

void SpawnSquare::spawnItem(Game &game)
{
  if(game.getCurrentTurn() %3 != 0)
  {
    return;
  }

  if(items_.empty() || current_item_on_square_ != nullptr)
  {
    return;
  }

  if(piece_ != nullptr && piece_->hasItem())
  {
    return;
  }
  ItemId id = items_.at(next_item_index_)->getId();
  std::unique_ptr<Item> spawned_item = Utils::copyItem(id, *(items_.at(next_item_index_).get()));

  next_item_index_++;
  if(next_item_index_ >= items_.size())
  {
    next_item_index_ = 0;
  }
  if(piece_ != nullptr)
  {
    piece_->addItem(std::move(spawned_item));
  }
  else
  {
    current_item_on_square_ = std::move(spawned_item);
  }
}

bool SpawnSquare::hasItem()
{
  if(current_item_on_square_ != nullptr)
  {
    return true;
  }
  return false;
}

std::unique_ptr<Item> SpawnSquare::releaseItem()
{
  return std::move(current_item_on_square_);
}

void SpawnSquare::setItems(std::vector<std::unique_ptr<Item>>& items)
{
  for (auto& item : items)
  {
    items_.push_back(Utils::copyItem(item->getId(), *(item.get())));
  }
}
