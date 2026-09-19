//----------------------------------------------------------------------------------------------------------------------
/// This class is responsible for validating and executing the effects of the UseCommand.
//----------------------------------------------------------------------------------------------------------------------

#include "UseCommand.hpp"
#include "Potion.hpp"

void UseCommand::execute(std::vector<std::string> parameters)
{
  if (parameters.size() < 1)
  {
    throw CustomException(error_messages_.at(ErrorType::INVALID_PARAMETER_COUNT));
  }
  else if (game_.AdditionalMove())
  {
    throw CustomException(error_messages_.at(ErrorType::SPECIAL_USE_UNAVAILABLE));
  }

  parseCoordinates(parameters.at(0), user_input_use_.square_);
  auto square = game_.getBoard().getSquare(user_input_use_.square_);

  if (!square->hasPiece() || *(square->getPiece()->getOwner()) != game_.getCurrentPlayer())
  {
    throw CustomException(error_messages_.at(ErrorType::PLAYER_PIECE_NOT_FOUND));
  }
  else if (!square->getPiece()->hasPotion())
  {
    throw CustomException(error_messages_.at(ErrorType::NO_POTION_FOUND));
  }

  Potion* potion = dynamic_cast<Potion*> (square->getPiece()->getItem());
  
  if (potion->getNumberExpectedParameters() != parameters.size())
  {
    throw CustomException(error_messages_.at(ErrorType::INVALID_PARAMETER_COUNT_USE));
  }
  else if (potion->getNumberExpectedParameters() >= 2)
  {
    parameters.erase(parameters.begin());
    if (!potion->validParameters(parameters, user_input_use_))
    {
      throw CustomException(error_messages_.at(ErrorType::INVALID_PARAMETER_USE));
    }
  }

  updateHistory();
  Piece* piece = square->getPiece();
  potion->usePotion(&game_, user_input_use_);
  piece->removeItem();
  game_.setPassiveCommand(false);
}

void UseCommand::updateHistory()
{
  auto used_item = game_.getBoard().getSquare(user_input_use_.square_)->getPiece()->getItem();
  std::string string = std::format(HISTORY_FORMAT_, used_item->getDisplayName(),
    static_cast<char>(tolower(user_input_use_.square_.getFile())), user_input_use_.square_.getRank());
  
  if (game_.getCurrentPlayer()->getHistory().size() != game_.getCurrentTurn())
  {
    game_.getCurrentPlayer()->getHistory().resize(game_.getCurrentTurn());
  }
  game_.getCurrentPlayer()->getHistory().at(game_.getCurrentTurn() - 1).push_back(string);
}
