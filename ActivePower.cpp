//---------------------------------------------------------------------------------------------------------------------
/// Base class for the special powers. It includes two constructors: with mana cost and without, virtual
/// destructor, and a default copy constructor. It contains several essential (pure) virtual functions that are used 
/// in the subclasses, as well as getter and setter.
//---------------------------------------------------------------------------------------------------------------------
#include "ActivePower.hpp"
#include "Game.hpp"

ActivePower::ActivePower(std::size_t mana_cost) : mana_cost_(mana_cost){}

void ActivePower::setMana(std::size_t amount)
{
  mana_cost_ = amount;
}

std::size_t ActivePower::getManaCost() const
{
  return mana_cost_;
}

bool ActivePower::validateMana(std::size_t player_mana)
{
  return player_mana >= mana_cost_;
}

void ActivePower::checkParameters(std::vector<std::string> parameters, UserInputSpecial& user_input_special,
  std::map<ErrorType, std::string>& error_messages)
{
  if (parameters.at(0).length() != 2)
  {
    throw CustomException(error_messages.at(ErrorType::INVALID_PARAMETER_SPECIAL_SQUARE));
  }
  else if ((parameters.at(0).at(0) >= 'A') && (parameters.at(0).at(0) <= 'H')
    && (parameters.at(0).at(1) >= '1') && (parameters.at(0).at(1) <= '8'))
  {
    user_input_special.target_square_ = Coordinates(parameters.at(0));
  }
  else
  {
    throw CustomException(error_messages.at(ErrorType::INVALID_PARAMETER_SPECIAL_SQUARE));
  }
}
