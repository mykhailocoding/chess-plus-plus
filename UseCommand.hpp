//----------------------------------------------------------------------------------------------------------------------
/// This class is responsible for validating and executing the effects of the UseCommand.
//----------------------------------------------------------------------------------------------------------------------

#ifndef USECOMMAND_HPP
#define USECOMMAND_HPP

#include "Command.hpp"
#include "Coordinates.hpp"

#include <string>
#include <format>
#include <string_view>

enum class Parity;

struct UserInputUse
{
  Coordinates square_;
  Coordinates target_square_;
  Parity parity_;
};

class UseCommand : public Command
{
  private:
    static constexpr std::string_view HISTORY_FORMAT_ = "{}{}{}";

    UserInputUse user_input_use_;
    
  public:
    //------------------------------------------------------------------------------------------------------------------
    /// @brief Constructor that creates a UseCommand object and initializes its member variables.
    /// @param game reference to the game object to give direct access to the game during command execution
    UseCommand(Game& game) : Command(game) {}

    //------------------------------------------------------------------------------------------------------------------
    /// @brief Copy constructor is deleted explicitly.
    UseCommand(const UseCommand&) = delete;

    //------------------------------------------------------------------------------------------------------------------
    /// @brief Destructor is declared explicitly as a default destructor.
    ~UseCommand() override = default;

    //------------------------------------------------------------------------------------------------------------------
    /// @brief This function is an overridden method of the base class to execute the effect of the UseCommand.
    /// @param parameters vector of parameters given by the user
    void execute(std::vector<std::string> parameters) override;

    //------------------------------------------------------------------------------------------------------------------
    /// @brief This function is an overridden method of the base class to update the current player's history.
    void updateHistory() override;
};

#endif
