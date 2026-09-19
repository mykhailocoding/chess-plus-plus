//----------------------------------------------------------------------------------------------------------------------
/// This class is responsible for validating and executing the effects of the SpecialCommand.
//----------------------------------------------------------------------------------------------------------------------

#include "SpecialCommand.hpp"
#include "Game.hpp"
#include "ActivePower.hpp"

void SpecialCommand::execute(std::vector<std::string> parameters)
{
  if (parameters.size() < 1)
  {
    throw CustomException(error_messages_.at(ErrorType::INVALID_PARAMETER_COUNT));
  }
  else if (game_.AdditionalMove())
  {
    throw CustomException(error_messages_.at(ErrorType::SPECIAL_USE_UNAVAILABLE));
  }

  parseCoordinates(parameters.at(0), user_input_special_.square_);
  validateParameters(parameters);

  auto current_piece = game_.getBoard().getSquare(user_input_special_.square_)->getPiece();
  current_piece->getPower()->usePower(&game_, user_input_special_);
  game_.setCurrentPiece(current_piece);
  game_.setPassiveCommand(false);
  updateHistory();
  if (game_.getBoard().getSquare(user_input_special_.square_)->getType() == SquareType::BOOST_SQUARE)
  {
    game_.setAdditionalMove(true);
  }
  else
  {
    game_.setAdditionalMove(false);
  }
}

void SpecialCommand::validateParameters(std::vector<std::string> parameters)
{
  if (!game_.getBoard().getSquare(user_input_special_.square_)->hasPiece())
  {
    throw CustomException(error_messages_.at(ErrorType::PLAYER_PIECE_NOT_FOUND));
  }

  auto current_piece = game_.getBoard().getSquare(user_input_special_.square_)->getPiece();

  if (current_piece->getOwner() != game_.getCurrentPlayer())
  {
    throw CustomException(error_messages_.at(ErrorType::PLAYER_PIECE_NOT_FOUND));
  }
  else if (!current_piece->hasSpecialPower())
  {
    throw CustomException(error_messages_.at(ErrorType::NO_SPECIAL_POWER));
  }
  else if (current_piece->getPower()->getNumberExpectedParameters() != parameters.size())
  {
    throw CustomException(error_messages_.at(ErrorType::INVALID_PARAMETER_COUNT_SPECIAL));
  }
  else if (current_piece->isFrozen())
  {
    throw CustomException(error_messages_.at(ErrorType::PIECE_FROZEN));
  }
  else if (current_piece->getPower()->getNumberExpectedParameters() >= 2)
  {
    parameters.erase(parameters.begin());
    current_piece->getPower()->checkParameters(parameters, user_input_special_, error_messages_);
  }
}

void SpecialCommand::updateHistory()
{
  std::string current_move = std::format(HISTORY_FORMAT_,
    static_cast<char>(tolower(user_input_special_.square_.getFile())), user_input_special_.square_.getRank());
  if (game_.getCurrentPlayer()->getHistory().size() != game_.getCurrentTurn())
  {
    game_.getCurrentPlayer()->getHistory().resize(game_.getCurrentTurn());
  }
  game_.getCurrentPlayer()->getHistory().at(game_.getCurrentTurn() - 1).push_back(current_move);
}
