//----------------------------------------------------------------------------------------------------------------------
/// This file contains the abstract base for commands and some simple Command classes that only use one execute method.
//----------------------------------------------------------------------------------------------------------------------

#ifndef COMMAND_HPP
#define COMMAND_HPP

#include "Exceptions.hpp"
#include "CommandParser.hpp"
#include "Conditions.hpp"

class Game;
enum class ErrorType;
class Piece;

#include <vector>
#include <string>
#include <map>

struct PieceShortNameAndManaCost
{
  std::string short_name;
  int mana_cost;
};

class Command
{
  protected:
    Game &game_;
    Piece *current_piece_;
    std::map<ErrorType, std::string> error_messages_;

  public:
    //------------------------------------------------------------------------------------------------------------------
    /// @brief Constructor that creates a Command object and initializes its member variables.
    /// @param game reference to the game object to give direct access to the game during command execution
    Command(Game &game);

    //------------------------------------------------------------------------------------------------------------------
    /// @brief Copy constructor is deleted explicitly.
    Command(const Command &) = delete;

    //------------------------------------------------------------------------------------------------------------------
    /// @brief Destructor is declared explicitly as a default destructor and is virtual because Command is a base class.
    virtual ~Command() = default;

    //------------------------------------------------------------------------------------------------------------------
    /// @brief This function is a pure virtual method for executing the effect of each specific command.
    /// @param parameters vector of parameters given by the user
    virtual void execute(std::vector<std::string> parameters) = 0;

    //------------------------------------------------------------------------------------------------------------------
    /// @brief This function updates the history of a player if the command was successfully executed.
    virtual void updateHistory() {};

    //------------------------------------------------------------------------------------------------------------------
    /// @brief This function parses and validates coordinate from user input and initializes the correct variable.
    /// @param coordinate possible coordinate entered by the user
    /// @param square reference to the variable where the square should be stored
    virtual void parseCoordinates(std::string coordinate, Coordinates& square);
};

class QuitCommand : public Command
{
  public:
    //------------------------------------------------------------------------------------------------------------------
    /// @brief Constructor that creates a QuitCommand object and initializes its member variables.
    /// @param game reference to the game object to give direct access to the game during command execution
    QuitCommand(Game &game) : Command(game) {};

    //------------------------------------------------------------------------------------------------------------------
    /// @brief Copy constructor is deleted explicitly.
    QuitCommand(const QuitCommand &) = delete;

    //------------------------------------------------------------------------------------------------------------------
    /// @brief Destructor is declared explicitly as a default destructor.
    ~QuitCommand() = default;

    //------------------------------------------------------------------------------------------------------------------
    /// @brief This function is an overridden method of the base class to execute the effect of the QuitCommand.
    /// @param parameters vector of parameters given by the user
    void execute(std::vector<std::string> parameters) override;
};

class BoardCommand : public Command
{
  public:
    //------------------------------------------------------------------------------------------------------------------
    /// @brief Constructor that creates a BoardCommand object and initializes its member variables.
    /// @param game reference to the game object to give direct access to the game during command execution
    BoardCommand(Game &game) : Command(game) {};

    //------------------------------------------------------------------------------------------------------------------
    /// @brief Copy constructor is deleted explicitly.
    BoardCommand(const BoardCommand &) = delete;

    //------------------------------------------------------------------------------------------------------------------
    /// @brief Destructor is declared explicitly as a default destructor.
    ~BoardCommand() = default;

    //------------------------------------------------------------------------------------------------------------------
    /// @brief This function is an overridden method of the base class to execute the effect of the BoardCommand.
    /// @param parameters vector of parameters given by the user
    void execute(std::vector<std::string> parameters) override;
};

class HelpCommand : public Command
{
  public:
    //------------------------------------------------------------------------------------------------------------------
    /// @brief Constructor that creates a HelpCommand object and initializes its member variables.
    /// @param game reference to the game object to give direct access to the game during command execution
    HelpCommand(Game &game) : Command(game) {};

    //------------------------------------------------------------------------------------------------------------------
    /// @brief Copy constructor is deleted explicitly.
    HelpCommand(const HelpCommand &) = delete;

    //------------------------------------------------------------------------------------------------------------------
    /// @brief Destructor is declared explicitly as a default destructor.
    ~HelpCommand() = default;

    //------------------------------------------------------------------------------------------------------------------
    /// @brief This function is an overridden method of the base class to execute the effect of the HelpCommand.
    /// @param parameters vector of parameters given by the user
    void execute(std::vector<std::string> parameters) override;
};

class HistoryCommand : public Command
{
  public:
    //------------------------------------------------------------------------------------------------------------------
    /// @brief Constructor that creates a HistoryCommand object and initializes its member variables.
    /// @param game reference to the game object to give direct access to the game during command execution
    HistoryCommand(Game &game) : Command(game) {};

    //------------------------------------------------------------------------------------------------------------------
    /// @brief Copy constructor is deleted explicitly.
    HistoryCommand(const HistoryCommand &) = delete;

    //------------------------------------------------------------------------------------------------------------------
    /// @brief Destructor is declared explicitly as a default destructor.
    ~HistoryCommand() = default;

    //------------------------------------------------------------------------------------------------------------------
    /// @brief This function is an overridden method of the base class to execute the effect of the HistoryCommand.
    /// @param parameters vector of parameters given by the user
    void execute(std::vector<std::string> parameters) override;
};

class PrisonCommand : public Command
{
  private:
    static constexpr std::string_view USER_INPUT_WHITE_ = "WHITE";
    static constexpr std::string_view USER_INPUT_BLACK_ = "BLACK";

  public:
    //------------------------------------------------------------------------------------------------------------------
    /// @brief Constructor that creates a PrisonCommand object and initializes its member variables.
    /// @param game reference to the game object to give direct access to the game during command execution
    PrisonCommand(Game &game) : Command(game) {};

    //------------------------------------------------------------------------------------------------------------------
    /// @brief Copy constructor is deleted explicitly.
    PrisonCommand(const PrisonCommand &) = delete;

    //------------------------------------------------------------------------------------------------------------------
    /// @brief Destructor is declared explicitly as a default destructor.
    ~PrisonCommand() = default;

    //------------------------------------------------------------------------------------------------------------------
    /// @brief This function is an overridden method of the base class to execute the effect of the PrisonCommand.
    /// @param parameters vector of parameters given by the user
    void execute(std::vector<std::string> parameters) override;
};

class InfoCommand : public Command
{
  private:
    static const std::map<std::string, PieceShortNameAndManaCost> SHORT_NAMES_AND_MANA_COST_;
    static const std::map<std::string, std::string> PIECE_IDS_;

  public:
    //------------------------------------------------------------------------------------------------------------------
    /// @brief Constructor that creates an InfoCommand object and initializes its member variables.
    /// @param game reference to the game object to give direct access to the game during command execution
    InfoCommand(Game &game) : Command(game) {};

    //------------------------------------------------------------------------------------------------------------------
    /// @brief Copy constructor is deleted explicitly.
    InfoCommand(const InfoCommand &) = delete;

    //------------------------------------------------------------------------------------------------------------------
    /// @brief Destructor is declared explicitly as a default destructor.
    ~InfoCommand() = default;

    //------------------------------------------------------------------------------------------------------------------
    /// @brief This function is an overridden method of the base class to execute the effect of the InfoCommand.
    /// @param parameters vector of parameters given by the user
    void execute(std::vector<std::string> parameters) override;
};

class PassCommand : public Command
{
  public:
    //------------------------------------------------------------------------------------------------------------------
    /// @brief Constructor that creates a PassCommand object and initializes its member variables.
    /// @param game reference to the game object to give direct access to the game during command execution
    PassCommand(Game& game) : Command(game) {};

    //------------------------------------------------------------------------------------------------------------------
    /// @brief Copy constructor is deleted explicitly.
    PassCommand(const PassCommand&) = delete;

    //------------------------------------------------------------------------------------------------------------------
    /// @brief Destructor is declared explicitly as a default destructor.
    ~PassCommand() = default;

    //------------------------------------------------------------------------------------------------------------------
    /// @brief This function is an overridden method of the base class to execute the effect of the PassCommand.
    /// @param parameters vector of parameters given by the user
    void execute(std::vector<std::string> parameters) override;
};

class ResignCommand : public Command
{
  public:
    //------------------------------------------------------------------------------------------------------------------
    /// @brief Constructor that creates a ResignCommand object and initializes its member variables.
    /// @param game reference to the game object to give direct access to the game during command execution
    ResignCommand(Game& game) : Command(game) {};

    //------------------------------------------------------------------------------------------------------------------
    /// @brief Copy constructor is deleted explicitly.
    ResignCommand(const ResignCommand&) = delete;

    //------------------------------------------------------------------------------------------------------------------
    /// @brief Destructor is declared explicitly as a default destructor.
    ~ResignCommand() = default;

    //------------------------------------------------------------------------------------------------------------------
    /// @brief This function is an overridden method of the base class to execute the effect of the ResignCommand.
    /// @param parameters vector of parameters given by the user
    void execute(std::vector<std::string> parameters) override;
};

class DrawCommand : public Command
{
  private:
    static constexpr std::string_view PLAYER_OFFERED_DRAW_MESSAGE_ =
      "Player {} has offered a draw. Would you like to accept? (yes/no)";
    static constexpr std::string_view USER_INPUT_YES_ = "YES";
    static constexpr std::string_view USER_INPUT_NO_ = "NO";

  public:
    //------------------------------------------------------------------------------------------------------------------
    /// @brief Constructor that creates a DrawCommand object and initializes its member variables.
    /// @param game reference to the game object to give direct access to the game during command execution
    DrawCommand(Game& game) : Command(game) {};

    //------------------------------------------------------------------------------------------------------------------
    /// @brief Copy constructor is deleted explicitly.
    DrawCommand(const DrawCommand&) = delete;

    //------------------------------------------------------------------------------------------------------------------
    /// @brief Destructor is declared explicitly as a default destructor.
    ~DrawCommand() = default;

    //------------------------------------------------------------------------------------------------------------------
    /// @brief This function is an overridden method of the base class to execute the effect of the DrawCommand.
    /// @param parameters vector of parameters given by the user
    void execute(std::vector<std::string> parameters) override;
};

#endif
