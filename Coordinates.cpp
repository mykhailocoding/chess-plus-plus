//---------------------------------------------------------------------------------------------------------------------
/// This class represents coordinates of the chessboard. Coordinates consists of two parameters: file and rank. Class
/// has three constructors, default copy constructor, default destructor, method to check the back rank coordinates and
/// getters/setters.
//---------------------------------------------------------------------------------------------------------------------
#include "Coordinates.hpp"
#include "Utils.hpp"
#include "Player.hpp"

Coordinates::Coordinates() {}

Coordinates::Coordinates(char file, std::size_t rank) : file_(file), rank_(rank) {}

Coordinates::Coordinates(std::string coordinates) : file_(coordinates.front())
{
 coordinates.erase(0, 1);
 Utils::stringToSizeT(coordinates, rank_);
}

bool Coordinates::validBackRankCoords(std::string player_id)
{
  if (player_id == WHITE_ID)
  {
    if ((file_ >= 'A') && (file_ <= 'H') && (rank_ == 1))
    {
      return true;
    }
    else
    {
      return false;
    }
  }
  else
  {
    if ((file_ >= 'A') && (file_ <= 'H') && (rank_ == 8))
    {
      return true;
    }
    else
    {
      return false;
    }
  }
}
