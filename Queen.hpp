//----------------------------------------------------------------------------------------------------------------------
/// Inherits from the base Piece class and implements checks for queen-specific movement 
/// and capture rules
//----------------------------------------------------------------------------------------------------------------------

#ifndef QUEEN_HPP
#define QUEEN_HPP
#include "Piece.hpp"

class Square;
class Board;

class Queen : public Piece
{
  public:
    //-----------------------------------------------------------------------------------------------------------------
    /// @brief constructor creates a Rook object and initializes its member variables 
    Queen();

    //-----------------------------------------------------------------------------------------------------------------
    /// @brief Constructs a new Queen object with specific attributes 
    /// @param id string identifier for the piece 
    /// @param special_power_type classification of the piece's special power 
    /// @param short_name visual representation of the piece on the board
    Queen(std::string id, SpecialPowerType special_power_type, std::string short_name);

    //-----------------------------------------------------------------------------------------------------------------
    /// @brief Copy constructor to create a copy of a pawn
    /// @param piece Queen that should be copied
    Queen(const Queen& piece) : Piece(piece) {}

    //-----------------------------------------------------------------------------------------------------------------
    /// @brief virtual destructor for the Pawn class set to default
    virtual ~Queen() override = default;

    //-----------------------------------------------------------------------------------------------------------------
    /// @brief Checks if the attempet move is allowed onto to the target square
    /// @param board current state of the game board
    /// @param target_square square the Queen intends to move to
    /// @return returns true if the move is allowed according to Queen rules, otherwise false
    bool isMoveValid(Board& board, Square* target_square) override;
};

#endif
