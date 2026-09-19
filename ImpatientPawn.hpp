//----------------------------------------------------------------------------------------------------------------------
/// Inherits from the Pawn class and initializes the piece with its 
/// specific identifier, visual representation, and unique active power
//----------------------------------------------------------------------------------------------------------------------



#ifndef IMPATIENT_PAWN_HPP
#define IMPATIENT_PAWN_HPP
#include "Pawn.hpp"
#include "ImpatientPawnPower.hpp"
#include <cstddef>//size_t

class ImpatientPawn : public Pawn
{
  public:
    //-----------------------------------------------------------------------------------------------------------------
    /// @brief constructor creates a ImpatientPawn object and initializes its member variables 
    ImpatientPawn();

    //-----------------------------------------------------------------------------------------------------------------
    /// @brief Copy constructor to create a copy of a I
    /// @param piece ImpatientPawnthat should be copied
    ImpatientPawn(const ImpatientPawn& piece) : Pawn(piece) {}

    //-----------------------------------------------------------------------------------------------------------------
    /// @brief virtual destructor for the ImpatientPawn class set to default
    ~ImpatientPawn() override = default;
};

#endif
