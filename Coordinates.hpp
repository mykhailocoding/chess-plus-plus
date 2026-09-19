//---------------------------------------------------------------------------------------------------------------------
/// This class represents coordinates of the chessboard. Coordinates consists of two parameters: file and rank. Class
/// has three constructors, default copy constructor, default destructor, method to check the back rank coordinates and
/// getters/setters.
//---------------------------------------------------------------------------------------------------------------------
#ifndef COORDINATES_HPP
#define COORDINATES_HPP
#include <cstddef>//for size_t
#include <string>

class Coordinates
{
  protected:
    char file_;//A-H
    std::size_t rank_;//1-8
  public:
    //-----------------------------------------------------------------------------------------------------------------
    /// @brief Default constructor.
    Coordinates();

    //-----------------------------------------------------------------------------------------------------------------
    /// @brief Constructor with specified coordinates.
    /// @param file file parameter
    /// @param rank rank parameter
    Coordinates(char file, std::size_t rank);

    //-----------------------------------------------------------------------------------------------------------------
    /// @brief Constructor with specified coordinates given as a string.
    /// @param coordinates string containing coordinate parameters
    Coordinates(std::string coordinates);

    //-----------------------------------------------------------------------------------------------------------------
    /// @brief Default copy constructor.
    Coordinates(const Coordinates& other) = default;
    
    //-----------------------------------------------------------------------------------------------------------------
    /// @brief Default copy assignment operator.
    /// @param other object to copy data from
    /// @return reference to the updated Coordinates object (*this)
    Coordinates& operator=(const Coordinates& other) = default;

    //-----------------------------------------------------------------------------------------------------------------
    /// @brief Default destructor.
    ~Coordinates() = default;

    //-----------------------------------------------------------------------------------------------------------------
    /// @brief Gets the file of the coordinates.
    /// @return file character
    char getFile() const
    {
      return file_;
    }

    //-----------------------------------------------------------------------------------------------------------------
    /// @brief Gets the rank of the coordinates.
    /// @return rank number
    std::size_t getRank() const
    {
      return rank_;
    }

    //-----------------------------------------------------------------------------------------------------------------
    /// @brief Sets the file of the coordinates.
    /// @param file file character
    void setFile(char file)
    {
      file_ = file;
    }

    //-----------------------------------------------------------------------------------------------------------------
    /// @brief Sets the rank of the coordinates.
    /// @param rank rank number
    void setRank(std::size_t rank)
    {
      rank_ = rank;
    }

    //-----------------------------------------------------------------------------------------------------------------
    /// @brief Checks if two coordinates are equal.
    /// @param other coordinates to compare against
    /// @return true if both file and rank match, false otherwise
    bool operator==(const Coordinates& other) const
    {
      return file_ == other.file_ && rank_ == other.rank_;
    }

    //-----------------------------------------------------------------------------------------------------------------
    /// @brief Checks if two coordinates are not equal.
    /// @param other coordinates to compare against
    /// @return true if either file or rank differs, false otherwise
    bool operator!=(const Coordinates& other) const{
      return file_ != other.file_ || rank_ != other.rank_;
    }

    //-----------------------------------------------------------------------------------------------------------------
    /// @brief Checks that the coordinates determine a back rank of the board relative to the specified player.
    /// @param player_id id of the specified player
    /// @return true if the coordinates are on the back rank, false otherwise
    bool validBackRankCoords(std::string player_id);
};

#endif
