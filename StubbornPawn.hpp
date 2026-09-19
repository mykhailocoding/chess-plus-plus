//----------------------------------------------------------------------------------------------------------------------
/// Inherits from the Pawn class and initializes the piece with its 
/// specific identifier, visual representation, and unique active power
//----------------------------------------------------------------------------------------------------------------------


#ifndef STUBBORN_PAWN_HPP
#define STUBBORN_PAWN_HPP
#include "Pawn.hpp"
#include "StubbornPawnPower.hpp"
#include <memory>

class StubbornPawn : public Pawn
{
  public:
    //-----------------------------------------------------------------------------------------------------------------
    /// @brief constructor creates a StubbornPawn object and initializes its member variables 
    StubbornPawn();

    //-----------------------------------------------------------------------------------------------------------------
    /// @brief Copy constructor to create a copy of a IceKnight
    /// @param piece StubbornPawn that should be copied
    StubbornPawn(const StubbornPawn& piece) : Pawn(piece) {}

    //-----------------------------------------------------------------------------------------------------------------
    /// @brief virtual destructor for the StubbornPawn class set to defaul
    ~StubbornPawn() override = default;
};

#endif
