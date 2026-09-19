//----------------------------------------------------------------------------------------------------------------------
/// Inherits from the Queen class and initializes the piece with its 
/// specific identifier, visual representation, and unique active power
//----------------------------------------------------------------------------------------------------------------------


#include "JumpyQueen.hpp"

JumpyQueen::JumpyQueen() : Queen("QJMP", SpecialPowerType::Active, "♛qj")
  {
    this->power_ = std::make_unique<JumpyQueenPower>();//adding power
  }