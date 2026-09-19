//----------------------------------------------------------------------------------------------------------------------
/// This class is responsible for parsing the user input and calling functions to execute its effect.
//----------------------------------------------------------------------------------------------------------------------

#ifndef COMMANDPARSER_HPP
#define COMMANDPARSER_HPP

class Game;
class Player;
class Piece;
class Square;
class Command;
class MoveCommand;
class SpecialCommand;
class UseCommand;
class Bishop;
class Coordinates;

#include <map>
#include <string>
#include <memory>
#include <functional>
#include <string_view>

class CommandParser
{
  private:
    static constexpr std::string_view PLACING_PIECES_FORMAT_ = "Where do you want to place {} ({} remaining)?";
    static const std::string USER_INPUT_QUIT_;
    static const std::string USER_INPUT_AUTO_;
    static const std::string INPUT_PROMPT_;
    static const std::map<std::string, std::function<std::unique_ptr<Command>(Game& game)>> COMMANDS_;
    
    Game& game_;
  
  public:
    //------------------------------------------------------------------------------------------------------------------
    /// @brief Constructor creates a CommandParser object and initializes its member variable.
    /// @param game reference to the game object to give direct access to the game during command execution
    CommandParser(Game& game) : game_(game) {}

    //------------------------------------------------------------------------------------------------------------------
    /// @brief Copy constructor is deleted explicitly.
    CommandParser(const CommandParser&) = delete;

    //------------------------------------------------------------------------------------------------------------------
    /// @brief Destructor is declared explicitly as a default destructor.
    ~CommandParser() = default;

    //------------------------------------------------------------------------------------------------------------------
    /// @brief This function reads user input from the terminal and validates it for a simple quit command.
    /// @param player player that is prompted for input
    /// @return Trimmed and normalized user input as a string.
    std::string getUserInput(Player* player);

    //------------------------------------------------------------------------------------------------------------------
    /// @brief This function handles the logic of placing the pieces of a player on the board at game start.
    /// @param player player that currently needs to place a piece of theirs on the board
    /// @param back_rank vector of pieces specified in the game config file that the player needs to place
    /// @param game reference to the game so the board can be modified during placing
    void placePiece(Player* player, std::vector<std::unique_ptr<Piece>>& back_rank, Game& game);

    //------------------------------------------------------------------------------------------------------------------
    /// @brief This function automatically places the remaining pieces on the board on the free places
    /// @param player player that wants to automatically place their pieces
    /// @param back_rank vector of pieces specified in the game config file that the player needs to place
    /// @param game reference to the game so the board can be modified during placing
    void autoPlacePieces(Player* player, std::vector<std::unique_ptr<Piece>>& back_rank, Game& game);

    //------------------------------------------------------------------------------------------------------------------
    /// @brief This function handles the initialisation of a pieces member variables.
    /// @param coordinate coordinate the piece is being placed on
    /// @param player player that places the piece on the board
    /// @param back_rank vector of pieces specified in the game config file that the player needs to place
    /// @param game reference to the game so the board can be modified during placing
    void registerPiece(Coordinates coordinate, Player* player, std::vector<std::unique_ptr<Piece>>& back_rank,
      Game& game);

    //------------------------------------------------------------------------------------------------------------------
    /// @brief This function starts the execution of a valid command and throws an exception if the command
    ///        doesn't exist.
    /// @param input trimmed and normalized user input
    void execute(std::string input);
};

#endif
