//----------------------------------------------------------------------------------------------------------------------
/// Inherits from the Rook class and initializes the piece with its 
/// specific identifier, visual representation, and unique active power
//----------------------------------------------------------------------------------------------------------------------


#include "InvincibleRook.hpp"

InvincibleRook::InvincibleRook() : Rook("RINV", SpecialPowerType::Active, "♜ri")
  {
    this->power_ = std::make_unique<InvincibleRookPower>();//adding power
  }
