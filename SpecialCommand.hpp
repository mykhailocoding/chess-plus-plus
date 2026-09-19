//----------------------------------------------------------------------------------------------------------------------
/// This class is responsible for validating and executing the effects of the SpecialCommand.
//----------------------------------------------------------------------------------------------------------------------

#ifndef SPECIALCOMMAND_HPP
#define SPECIALCOMMAND_HPP

#include "Command.hpp"
#include "Coordinates.hpp"

#include <string>
#include <format>

struct UserInputSpecial
{
  Coordinates square_;
  Coordinates target_square_;
  Coordinates bounce_square_;
  std::size_t turn_count_;
  char piece_type_;
};

class SpecialCommand : public Command
{
  private:
    static constexpr std::string_view HISTORY_FORMAT_ = "S{}{}";

    UserInputSpecial user_input_special_;
    
  public:
    //------------------------------------------------------------------------------------------------------------------
    /// @brief Constructor that creates a SpecialCommand object and initializes its member variables.
    /// @param game reference to the game object to give direct access to the game during command execution
    SpecialCommand(Game& game) : Command(game) {};

    //------------------------------------------------------------------------------------------------------------------
    /// @brief Copy constructor is deleted explicitly.
    SpecialCommand(const SpecialCommand&) = delete;

    //------------------------------------------------------------------------------------------------------------------
    /// @brief Destructor is declared explicitly as a default destructor.
    ~SpecialCommand() = default;

    //------------------------------------------------------------------------------------------------------------------
    /// @brief This function is an overridden method of the base class to execute the effect of the SpecialCommand.
    /// @param parameters vector of parameters given by the user
    void execute(std::vector<std::string> parameters) override;

    //------------------------------------------------------------------------------------------------------------------
    /// @brief This function checks if the move entered by user was a valid special or not.
    /// @param parameters vector of parameters given by the user
    void validateParameters(std::vector<std::string> parameters);

    //------------------------------------------------------------------------------------------------------------------
    /// @brief This function is an overridden method of the base class to update the current player's history.
    void updateHistory() override;
};

#endif
