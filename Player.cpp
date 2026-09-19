//---------------------------------------------------------------------------------------------------------------------
/// This class represents a player. Contains essential members such as: id, mana, prison, history and others. Also has
/// getters/setters and some methods.
//---------------------------------------------------------------------------------------------------------------------
#include "Player.hpp"
#include "Piece.hpp"
#include "Utils.hpp"

Player::Player(std::string id, std::size_t mana, std::size_t elo_score, std::size_t mana_pool) :
  id_(id),
  current_mana_(mana),
  elo_score_(elo_score),
  mana_pool_(mana_pool),
  status_(PlayerStatus::NONE) {}

Player::Player(const Player& player) : id_(player.id_), current_mana_(player.current_mana_),
  elo_score_(player.elo_score_), mana_pool_(player.mana_pool_), history_(player.history_), status_(player.status_)
  {
    if (player.prison_.size() != 0)
    {
      for (auto& piece : player.prison_)
      {
        prison_.push_back(Utils::copyPiece(piece->getId(), *(piece.get())));
      }
    }
  }


//we always check if the player has enough mana beforehand
//here we subtract only
void Player::reduceMana(size_t mana_cost)
{
  current_mana_ -= mana_cost;
}

void Player::addPieceToPrison(std::unique_ptr<Piece> piece)
{
  piece->setOwner(nullptr);
  prison_.push_back(std::move(piece));
}

void Player::addMana(std::size_t mana_to_add)
{
  if ((current_mana_ + mana_to_add) <= mana_pool_)
  {
    current_mana_ += mana_to_add;
  }
  else
  {
    current_mana_ = mana_pool_;
  }
}

bool Player::operator==(Player* rhs_player)
{
  if (id_ == rhs_player->getId())
  {
    return true;
  }
  else
  {
    return false;
  }
}

bool Player::operator!=(Player* rhs_player)
{
  if (id_ != rhs_player->getId())
  {
    return true;
  }
  else
  {
    return false;
  }
}

bool Player::isCheckMated()
{
  if (status_ == PlayerStatus::CHECK_MATE)
  {
    return true;
  }
  else
  {
    return false;
  }
}

bool Player::isStaleMated()
{
  if (status_ == PlayerStatus::STALE_MATE)
  {
    return true;
  }
  else
  {
    return false;
  }
}
