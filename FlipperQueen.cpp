//----------------------------------------------------------------------------------------------------------------------
/// Inherits from the Queen class and initializes the piece with its 
/// specific identifier, visual representation, and unique active power.
//----------------------------------------------------------------------------------------------------------------------


#include "FlipperQueen.hpp"

FlipperQueen::FlipperQueen() : Queen("QFLP", SpecialPowerType::Active, "♛qf")
  {
    this->power_ = std::make_unique<FlipperQueenPower>();//adding power
  }

