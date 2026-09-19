//----------------------------------------------------------------------------------------------------------------------
/// Inherits from the Bishop class and initializes the piece with its 
/// specific identifier, visual representation, and unique active power
//----------------------------------------------------------------------------------------------------------------------


#include "PreacherBishop.hpp"

PreacherBishop::PreacherBishop() : Bishop("BPRC", SpecialPowerType::Active, "♝bp")
  {
    this->power_ = std::make_unique<PreacherBishopPower>();//adding power
  }

