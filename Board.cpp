//----------------------------------------------------------------------------------------------------------------------
/// This class creates the board object that prints the board onto the console, replaces and gets squares on the board.
//----------------------------------------------------------------------------------------------------------------------

#include "Board.hpp"
#include "Game.hpp"
#include "Square.hpp"
#include "BoostSquare.hpp"
#include "ManaSquare.hpp"
#include "SpawnSquare.hpp"
#include "Player.hpp"
#include "Piece.hpp"

Board::Board() : is_active_(true)
{
  for (int rank_number = 1; rank_number <= 8; rank_number++)
  {
    std::vector<Square*> rank;
    for (char file = 'A'; file <= 'H'; file++)
    {
      Coordinates coordinates(file, rank_number);
      if (rank_number % 2 == 1)
      {
        if (file % 2 == 1)
        {
          rank.push_back(new Square(SquareType::BASIC_BLACK, coordinates));
        }
        else
        {
          rank.push_back(new Square(SquareType::BASIC_WHITE, coordinates));
        }
      }
      else
      {
        if (file % 2 == 0)
        {
          rank.push_back(new Square(SquareType::BASIC_BLACK, coordinates));
        }
        else
        {
          rank.push_back(new Square(SquareType::BASIC_WHITE, coordinates));
        }
      }
    }
    
    board_.push_back(rank);
  }
}

Board::Board(const Board& other_board) : is_active_(other_board.is_active_)
{
  for (auto rank : other_board.board_)
  {
    std::vector<Square*> new_rank;
    for (auto square : rank)
    {
      new_rank.push_back(Utils::copySquare(square->getType(), *square));
    }
    board_.push_back(new_rank);
  }
}

Board::~Board()
{
  for (auto &row : board_)
  {
    for (Square *square : row)
    {
      delete square;
    }
  }
}

std::vector<std::vector<Square*>>& Board::getBoard() { return board_; }

void Board::setBoard(std::vector<std::vector<Square*>>& board)
{
  board_ = board;
}

Square* Board::getSquare(Coordinates coordinates)
{
  for (auto &row : board_)
  {
    for (auto& square : row)
    {
      if (square->getCoordinates() == coordinates)
      {
        return square;
      }
    }
  }

  // technically not possible that the wanted coordinate is not found
  return nullptr;
}


void Board::setSquare(Coordinates coordinates, SquareType square_type)
{
  size_t file = coordinates.getFile() - 'A';
  size_t rank = coordinates.getRank() - 1;
  delete board_[rank][file];
  
  switch(square_type)
  {
  case SquareType::BASIC_BLACK:
    board_[rank][file] = new Square(SquareType::BASIC_BLACK, coordinates);
    break;
  case SquareType::BASIC_WHITE :
    board_[rank][file] = new Square(SquareType::BASIC_WHITE, coordinates);
    break;
  case SquareType::BOOST_SQUARE :
    board_[rank][file] = new BoostSquare(coordinates);
    break;
  case SquareType::MANA_SQUARE :
    board_[rank][file] = new ManaSquare(coordinates);
    break;
  case SquareType::SPAWN_SQUARE :
    board_[rank][file] = new SpawnSquare(coordinates);
    break;
  }
}


void Board::printBoard( Game &game, const Player &white_player, const Player &black_player)
{
  if (!is_active_)
  {
    return;
  }
  
  std::cout << game.getDescriptionMapping().at("CHESSBOARD_BORDER") << std::endl;
  std::cout << game.getDescriptionMapping().at("BORDER_D") << std::endl;
  std::cout << "Turn " << game.getCurrentTurn() << " / " << game.getMaxTurnCount() << "\n"
            << std::endl;

  const Player *current_player;
  const Player *opponent_player;
  std::string top_color_display;
  std::string bottom_color_display;

  // Black is playing
  if (game.getCurrentPlayer()->getId() == BLACK_ID)
  {
    current_player = &black_player;
    opponent_player = &white_player;
    top_color_display = "White mana: ";
    bottom_color_display = "Black mana: ";
  }
  else // white is playing
  {
    current_player = &white_player;
    opponent_player = &black_player;
    top_color_display = "Black mana: ";
    bottom_color_display = "White mana: ";
  }

  std::cout << top_color_display << opponent_player->getCurrentMana() << "/" << game.getManaPool() << "\n"
            << std::endl;

  if (current_player == &white_player)
  {
    for (int row = 7; row >= 0; row--)
    {
      std::cout << row + 1 << " ";
      for (int column = 0; column < 8; column++)
      {

        if (board_[row][column] != nullptr)
        {
          board_[row][column]->print(game);
        }
      }
      std::cout << "\n";
    }
    std::cout << " ";
    for (std::size_t column = 0; column < 8; column++)
    {
      
      std::cout<< "   " <<static_cast<char>('A'+ column);
    }
  }

  if (current_player == &black_player)
  {
    for (int row = 0; row < 8; row++)
    {
      std::cout << row+1 << " ";
      for (int column = 7; column >= 0; column--)
      {
        if (board_[row][column] != nullptr)
        {
          board_[row][column]->print(game);
        }
      }
      std::cout << "\n";
    }
    std::cout << " ";
    for (int column = 7; column >= 0; column--)
    {
      std::cout<< "   " << static_cast<char>('A' + column);
    }
  }
  std::cout << "\n\n";
  std::cout << bottom_color_display << current_player->getCurrentMana() << "/" << game.getManaPool() << "\n";
  std::cout << game.getDescriptionMapping().at("BORDER_D") << std::endl;
}

void Board::toggleBoard()
{
  is_active_ = !is_active_;
}

Square* Board::getSquare(int row, int col) { return board_[row][col]; }
