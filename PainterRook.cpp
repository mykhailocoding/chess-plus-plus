//----------------------------------------------------------------------------------------------------------------------
/// Inherits from the Rook class and initializes the piece with its 
/// specific identifier, visual representation, and unique active power
//----------------------------------------------------------------------------------------------------------------------


#include "PainterRook.hpp"

PainterRook::PainterRook() : Rook("RPNT", SpecialPowerType::Active, "♜rp")
  {
    this->power_ = std::make_unique<PainterRookPower>();//adding power
  }
