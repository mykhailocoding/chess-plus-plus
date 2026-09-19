//----------------------------------------------------------------------------------------------------------------------
/// Inherits from the King class and initializes the piece with its 
/// specific identifier, visual representation, and unique active power
//----------------------------------------------------------------------------------------------------------------------

#include "ArcherKing.hpp"

ArcherKing::ArcherKing() : King("KARC", SpecialPowerType::Active, "♚ka")
  {
    this->power_ = std::make_unique<ArcherKingPower>();//adding power
  }

