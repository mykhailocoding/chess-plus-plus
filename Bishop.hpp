//----------------------------------------------------------------------------------------------------------------------
/// A subclass from piece and implements the checks if a bishop movement is allowed and creates bishop objects.
//----------------------------------------------------------------------------------------------------------------------
#ifndef BISHOP_HPP
#define BISHOP_HPP
#include "Piece.hpp"
#include <string>

class Board; 
class Square;
class ColorBlindBishop;

enum class MovementColor
{
  BLACK, 
  WHITE
};

class Bishop : public Piece
{
  protected:
    MovementColor movement_color_;
  public:
    //-----------------------------------------------------------------------------------------------------------------
    /// @brief Constructor creates a bishop object and initializes its member variables.
    Bishop();

    //-----------------------------------------------------------------------------------------------------------------
    /// @brief Constructor creates a new bishop object with speficic attribute (movement_color).
    /// @param movement_color the color the bishop is allowed to move along on 
    Bishop(char movement_color);

    //-----------------------------------------------------------------------------------------------------------------
    /// @brief Constructs a new Bishop object with specific attributes.
    /// @param id string identifier for the piece 
    /// @param special_power_type classification of the piece's special power 
    /// @param short_name visual representation of the piece on the board
    Bishop(std::string id, SpecialPowerType special_power_type, std::string short_name);

    //-----------------------------------------------------------------------------------------------------------------
    /// @brief Copy constructor to create a copy of a bishop.
    /// @param piece the Bishop that should be copied
    Bishop(const Bishop& piece) : Piece(piece), movement_color_(piece.movement_color_) {}

    //-----------------------------------------------------------------------------------------------------------------
    /// @brief Virtual destructor for the Bishop class set to default.
    virtual ~Bishop() override = default;

    //-----------------------------------------------------------------------------------------------------------------
    /// @brief Checks if the attempted move is allowed onto the target square.
    /// @param board current state of the game board
    /// @param target_square square the bishop intends to move to
    /// @return returns true if the move is allowed according to pawn rules, otherwise false
    bool isMoveValid(Board& board, Square* target_square)override;

    //-----------------------------------------------------------------------------------------------------------------
    /// @brief Sets the movement_color for the piece.
    /// @param color the color the member (movement_color) should be set to
    void setMovementColor(MovementColor color)
    {
      movement_color_ = color;
    }

    //-----------------------------------------------------------------------------------------------------------------
    /// @brief Gets the movement color of the bishop.
    /// @return current movement color
    MovementColor getMovementColor() const
    {
      return movement_color_;
    }
};

#endif
