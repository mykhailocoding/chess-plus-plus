//----------------------------------------------------------------------------------------------------------------------
/// Inherits from the base Piece class and implements checks for rook-specific movement 
/// and capture rules
//----------------------------------------------------------------------------------------------------------------------


#ifndef ROOK_HPP
#define ROOK_HPP
#include "Piece.hpp"

class Square;
class Board;

class Rook : public Piece
{
  public:
    //-----------------------------------------------------------------------------------------------------------------
    /// @brief constructor creates a Rook object and initializes its member variables 
    Rook();

    //-----------------------------------------------------------------------------------------------------------------
    /// @brief Constructs a new Rook object with specific attributes 
    /// @param id string identifier for the piece 
    /// @param special_power_type classification of the piece's special power 
    /// @param short_name visual representation of the piece on the board 
    Rook(std::string id, SpecialPowerType special_power_type, std::string short_name);

    //-----------------------------------------------------------------------------------------------------------------
    /// @brief Copy constructor to create a copy of a pawn
    /// @param piece Rook that should be copied
    Rook(const Rook& piece) : Piece(piece) {}

    //-----------------------------------------------------------------------------------------------------------------
    /// @brief virtual destructor for the Pawn class set to default
    virtual ~Rook() override = default;

    //-----------------------------------------------------------------------------------------------------------------
    /// @brief Checks if the attempet move is allowed onto to the target square
    /// @param board current state of the game board
    /// @param target_square square the Rook intends to move to
    /// @return returns true if the move is allowed according to rook rules, otherwise false
    bool isMoveValid(Board& board, Square* target_square) override;
};

#endif
