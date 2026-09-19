//----------------------------------------------------------------------------------------------------------------------
/// Inherits from the Knight class and checks JumpyKnight-specific movement 
/// and capture rules.
//----------------------------------------------------------------------------------------------------------------------


#ifndef JUMPY_KNIGHT_HPP
#define JUMPY_KNIGHT_HPP
#include "Knight.hpp"

class JumpyKnight : public Knight
{
  public:
    //-----------------------------------------------------------------------------------------------------------------
    /// @brief constructor creates a JumpyKnight object and initializes its member variables 
    JumpyKnight();

    //-----------------------------------------------------------------------------------------------------------------
    /// @brief Copy constructor to create a copy of a JumpyKnight
    /// @param piece JumpyKnight that should be copied
    JumpyKnight(const JumpyKnight& piece) : Knight(piece) {}

    //-----------------------------------------------------------------------------------------------------------------
    /// @brief virtual destructor for the IceKnight class set to default
    ~JumpyKnight() override = default;

    //-----------------------------------------------------------------------------------------------------------------
    /// @brief Checks if the attempet move is allowed onto the target square
    /// @param board current state of the game board, but is not used because the all pieces of type Knights can jump 
    // over pieces on the board and no chekcs if the path is clear are needed
    /// @param target_square square the JumpyKnight intends to move to
    /// @return returns true if the move is allowed according to JumpyKnight rules, otherwise false
    bool isMoveValid([[maybe_unused]] Board& board, Square* target_square) override;
};

#endif
