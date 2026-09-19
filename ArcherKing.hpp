//----------------------------------------------------------------------------------------------------------------------
/// Inherits from the King class and initializes the piece with its specific identifier, visual representation, and
/// unique active power.
//----------------------------------------------------------------------------------------------------------------------
#ifndef ARCHER_KING_HPP
#define ARCHER_KING_HPP
#include "King.hpp"
#include "ArcherKingPower.hpp"

class ArcherKing : public King
{
  public:
    //-----------------------------------------------------------------------------------------------------------------
    /// @brief Constructor creates a ArcherKing object and initializes its member variables.
    ArcherKing();

    //-----------------------------------------------------------------------------------------------------------------
    /// @brief Copy constructor to create a copy of a ArcherKing.
    /// @param piece ArcherKing that should be copied
    ArcherKing(const ArcherKing& piece) : King(piece) {}

    //-----------------------------------------------------------------------------------------------------------------
    /// @brief Virtual destructor for the ArcherKing class set to default.
    ~ArcherKing() override = default;
};

#endif
