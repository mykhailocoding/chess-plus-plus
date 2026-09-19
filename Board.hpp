//----------------------------------------------------------------------------------------------------------------------
/// This class creates the board object that prints the board onto the console, replaces and gets squares on the board.
//----------------------------------------------------------------------------------------------------------------------


#ifndef BOARD_HPP
#define BOARD_HPP

#include <vector>
#include <cstddef>
#include <iostream>
#include <memory>

#include "Coordinates.hpp"

//forward declarations
class Square;
class Player;
class Game;
enum class SquareType;

class Board
{
  private:
    std::vector<std::vector<Square*>> board_;
    bool is_active_;
  public:
  //--------------------------------------------------------------------------------------------------------------------
  /// @brief constructor creates a board object and initializies an 8x8 board with alternating black and white squares
  Board();

  //--------------------------------------------------------------------------------------------------------------------
  /// @brief Copy constructor to create a copy of the board
  /// @param other_board the board that should be copied
  Board(const Board& other_board);
  
  //--------------------------------------------------------------------------------------------------------------------
  /// @brief destructor deletes dynammically allocated squares on the board
  ~Board();
  
  //--------------------------------------------------------------------------------------------------------------------
  /// @brief getter for the 2D vector of the grid 
  /// @return returns a reference to the internal 2D vector of Square pointers
  std::vector<std::vector<Square*>>& getBoard();
  
  //--------------------------------------------------------------------------------------------------------------------
  /// @brief overwrites the current board layout with a new grid
  /// @param board the new 2D vector layout to layout with
  void setBoard(std::vector<std::vector<Square*>>& board);


  //--------------------------------------------------------------------------------------------------------------------
  /// @brief gets a square on the board with the coordinates of the square
  /// @param coordinates the coordinates of the square to be found
  /// @return pointer to the found square or nullptr if not found
  Square* getSquare(Coordinates coordinates);

  //--------------------------------------------------------------------------------------------------------------------
  /// @brief replaces an existing square with a new square 
  /// @param coordinates coordinates of the sqaure where the new square  should be 
  /// @param square_type the type the new square has
  void setSquare(Coordinates coordinates, SquareType square_type);

  //--------------------------------------------------------------------------------------------------------------------
  /// @brief prints the Board onto the console
  /// @param game the game being currently played with
  /// @param white_player the white Player of the game 
  /// @param black_player the black pplayer of the game 
  void printBoard(Game &game, const Player &white_player, const Player &black_player);

  //--------------------------------------------------------------------------------------------------------------------
  /// @brief toggles the active status flag of the board 
  void toggleBoard();

  //--------------------------------------------------------------------------------------------------------------------
  /// @brief gets a square on the board with the with the row and column of the square
  /// @param row row of the sqaure to be found
  /// @param column column of the sqaure to be found
  /// @return pointer to the found square or nullptr if not found
  Square* getSquare(int row, int column);
};

#endif
