//----------------------------------------------------------------------------------------------------------------------
/// Inherits from the Queen class and checks HungryQueen-specific movement 
/// and capture rules.
//----------------------------------------------------------------------------------------------------------------------


#ifndef HUNGRY_QUEEN_HPP
#define HUNGRY_QUEEN_HPP
#include "Queen.hpp"

class HungryQueen : public Queen
{
  public:
    //-----------------------------------------------------------------------------------------------------------------
    /// @brief constructor creates a HungryQueen object and initializes its member variables 
    HungryQueen();

    //-----------------------------------------------------------------------------------------------------------------
    /// @brief Copy constructor to create a copy of a HungryQueen
    /// @param piece HungryQueen that should be copied
    HungryQueen(const HungryQueen& piece) : Queen(piece) {}

    //-----------------------------------------------------------------------------------------------------------------
    /// @brief virtual destructor for the HungryQueen class set to default
    ~HungryQueen() override = default;

    //-----------------------------------------------------------------------------------------------------------------
    /// @brief Checks if the attempet move is allowed onto to the target square
    /// @param board current state of the game board
    /// @param target_square square the HungryQueen intends to move to
    /// @return returns true if the move is allowed according to HungryQueen rules, otherwise false
    bool isMoveValid(Board& board, Square* target_square) override;
};

#endif
