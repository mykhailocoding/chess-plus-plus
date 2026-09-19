//----------------------------------------------------------------------------------------------------------------------
/// Inherits from the base Piece class and implements checks for knight-specific movement 
/// and capture rules
//----------------------------------------------------------------------------------------------------------------------


#ifndef KNIGHT_HPP
#define KNIGHT_HPP
#include "Piece.hpp"

class Board;
class Square;

class Knight : public Piece
{
  public:
    //-----------------------------------------------------------------------------------------------------------------
    /// @brief constructor creates a Knight object and initializes its member variables 
    Knight();

    //-----------------------------------------------------------------------------------------------------------------
    /// @brief Constructs a new Knight object with specific attributes 
    /// @param id string identifier for the piece 
    /// @param special_power_type classification of the piece's special power 
    /// @param short_name visual representation of the piece on the board
    Knight(std::string id, SpecialPowerType special_power_type, std::string short_name);

    //-----------------------------------------------------------------------------------------------------------------
    /// @brief Copy constructor to create a copy of a knight
    /// @param piece Knight that should be copied
    Knight(const Knight& piece) : Piece(piece) {}

    //-----------------------------------------------------------------------------------------------------------------
    /// @brief virtual destructor for the Knight class set to default
    virtual ~Knight() override = default;

    //-----------------------------------------------------------------------------------------------------------------
    /// @brief Checks if the attempet move is allowed onto to the target square
    /// @param board current state of the game board, but is not used because the all pieces of type Knights can jump 
    // over pieces on the board and no chekcs if the path is clear are needed
    /// @param target_square square the knight intends to move to
    /// @return returns true if the move is allowed according to knight rules, otherwise false
    bool isMoveValid([[maybe_unused]] Board& board, Square* target_square)override;
};

#endif
