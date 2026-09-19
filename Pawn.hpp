//----------------------------------------------------------------------------------------------------------------------
/// Inherits from the base Piece class and implements checks for pawn-specific movement 
/// and capture rules.
//----------------------------------------------------------------------------------------------------------------------



#ifndef PAWN_HPP
#define PAWN_HPP
#include "Piece.hpp"

class Player;
class Board;
class Square;

class Pawn : public Piece
{
  public:
    //-----------------------------------------------------------------------------------------------------------------
    /// @brief constructor creates a Pawn object and initializes its member variables 
    Pawn();

    //-----------------------------------------------------------------------------------------------------------------
    /// @brief Constructs a new Pawn object with specific attributes 
    /// @param id string identifier for the piece 
    /// @param special_power_type classification of the piece's special power 
    /// @param short_name visual representation of the piece on the board 
    Pawn(std::string id, SpecialPowerType special_power_type, std::string short_name);

    //-----------------------------------------------------------------------------------------------------------------
    /// @brief Copy constructor to create a copy of a pawn
    /// @param piece Pawn that should be copied
    Pawn(const Pawn& piece) : Piece(piece) {};

    //-----------------------------------------------------------------------------------------------------------------
    /// @brief virtual destructor for the Pawn class set to default
    virtual ~Pawn() override = default;

    //-----------------------------------------------------------------------------------------------------------------
    /// @brief Checks if the attempet move is allowed onto to the target square
    /// @param board current state of the game board
    /// @param target_square square the pawn intends to move to
    /// @return returns true if the move is allowed according to pawn rules, otherwise false
    bool isMoveValid(Board& board, Square* target_square)override;
};

#endif
