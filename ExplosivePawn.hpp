//----------------------------------------------------------------------------------------------------------------------
/// Inherits from the Pawn class and initializes the piece with its 
/// specific identifier, visual representation, and unique active power
//----------------------------------------------------------------------------------------------------------------------


#ifndef EXPLOSIVE_PAWN_HPP
#define EXPLOSIVE_PAWN_HPP
#include "Pawn.hpp"
#include "ExplosivePawnPower.hpp"

class ExplosivePawn : public Pawn
{
  public:
    //-----------------------------------------------------------------------------------------------------------------
    /// @brief constructor creates a ExplosivePawn object and initializes its member variables 
    ExplosivePawn();

    //-----------------------------------------------------------------------------------------------------------------
    /// @brief Copy constructor to create a copy of a ExplosivePawn
    /// @param piece ExplosivePawn that should be copied
    ExplosivePawn(const ExplosivePawn& piece) : Pawn(piece) {}

    //-----------------------------------------------------------------------------------------------------------------
    /// @brief virtual destructor for the ExplosivePawn class set to default
    ~ExplosivePawn() override = default;
};

#endif
