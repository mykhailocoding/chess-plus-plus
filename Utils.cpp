//----------------------------------------------------------------------------------------------------------------------
/// The Utils class contains some useful functions for use in other classes. These include type conversions, 
/// trimming input, converting the case of strings as well as splitting a string into tokens.
///
/// Author(s): Tutors
///
/// we added a function to tokenize a string without trimming and to create/copy objects
//----------------------------------------------------------------------------------------------------------------------
#include "Utils.hpp"
#include "Pawn.hpp"
#include "GoldenPawn.hpp"
#include "ImpatientPawn.hpp"
#include "StubbornPawn.hpp"
#include "NervousPawn.hpp"
#include "ExplosivePawn.hpp"
#include "Rook.hpp"
#include "InvincibleRook.hpp"
#include "PainterRook.hpp"
#include "Knight.hpp"
#include "JumpyKnight.hpp"
#include "IceKnight.hpp"
#include "Bishop.hpp"
#include "ColorBlindBishop.hpp"
#include "PreacherBishop.hpp"
#include "Queen.hpp"
#include "FlipperQueen.hpp"
#include "JumpyQueen.hpp"
#include "HungryQueen.hpp"
#include "King.hpp"
#include "FrightenedKing.hpp"
#include "ArcherKing.hpp"
#include "FreezePotion.hpp"
#include "TeleportPotion.hpp"
#include "EvenOddPotion.hpp"
#include "SkywalkerPotion.hpp"
#include "Shield.hpp"
#include "InvisibilityCloak.hpp"
#include "QueenRepellant.hpp"
#include "ManaSquare.hpp"
#include "SpawnSquare.hpp"
#include "BoostSquare.hpp"
#include "ManaSquare.hpp"
#include "SpawnSquare.hpp"
#include "BoostSquare.hpp"

const std::map<std::string, std::function<std::unique_ptr<Piece>()>> Utils::PIECE_ID_CONSTRUCTOR_MAPPING_
{
  {"P",     []() { return std::make_unique<Pawn>(); }},
  {"PGLD",  []() { return std::make_unique<GoldenPawn>(); }},
  {"PIPT",  []() { return std::make_unique<ImpatientPawn>(); }},
  {"PSTB",  []() { return std::make_unique<StubbornPawn>(); }},
  {"PNRV",  []() { return std::make_unique<NervousPawn>(); }},
  {"PEXP",  []() { return std::make_unique<ExplosivePawn>(); }},
  {"R",     []() { return std::make_unique<Rook>(); }},
  {"RINV",  []() { return std::make_unique<InvincibleRook>(); }},
  {"RPNT",  []() { return std::make_unique<PainterRook>(); }},
  {"N",     []() { return std::make_unique<Knight>(); }},
  {"NJMP",  []() { return std::make_unique<JumpyKnight>(); }},
  {"NICE",  []() { return std::make_unique<IceKnight>(); }},
  {"B",     []() { return std::make_unique<Bishop>(); }},
  {"BCLR",  []() { return std::make_unique<ColorBlindBishop>(); }},
  {"BPRC",  []() { return std::make_unique<PreacherBishop>(); }},
  {"Q",     []() { return std::make_unique<Queen>(); }},
  {"QFLP",  []() { return std::make_unique<FlipperQueen>(); }},
  {"QJMP",  []() { return std::make_unique<JumpyQueen>(); }},
  {"QHNGR", []() { return std::make_unique<HungryQueen>(); }},
  {"K",     []() { return std::make_unique<King>(); }},
  {"KFRT",  []() { return std::make_unique<FrightenedKing>(); }},
  {"KARC",  []() { return std::make_unique<ArcherKing>(); }}
};

const std::map<std::string, std::function<std::unique_ptr<Piece>(const Piece& piece)>> Utils::PIECE_ID_COPY_CONSTRUCTOR_MAPPING_
{
  {"P",     [](const Piece& piece) { return std::make_unique<Pawn>(static_cast<const Pawn&>(piece)); }},
  {"PGLD",  [](const Piece& piece) { return std::make_unique<GoldenPawn>(static_cast<const GoldenPawn&>(piece)); }},
  {"PIPT",  [](const Piece& piece) { return std::make_unique<ImpatientPawn>(static_cast<const ImpatientPawn&>(piece)); }},
  {"PSTB",  [](const Piece& piece) { return std::make_unique<StubbornPawn>(static_cast<const StubbornPawn&>(piece)); }},
  {"PNRV",  [](const Piece& piece) { return std::make_unique<NervousPawn>(static_cast<const NervousPawn&>(piece)); }},
  {"PEXP",  [](const Piece& piece) { return std::make_unique<ExplosivePawn>(static_cast<const ExplosivePawn&>(piece)); }},
  {"R",     [](const Piece& piece) { return std::make_unique<Rook>(static_cast<const Rook&>(piece)); }},
  {"RINV",  [](const Piece& piece) { return std::make_unique<InvincibleRook>(static_cast<const InvincibleRook&>(piece)); }},
  {"RPNT",  [](const Piece& piece) { return std::make_unique<PainterRook>(static_cast<const PainterRook&>(piece)); }},
  {"N",     [](const Piece& piece) { return std::make_unique<Knight>(static_cast<const Knight&>(piece)); }},
  {"NJMP",  [](const Piece& piece) { return std::make_unique<JumpyKnight>(static_cast<const JumpyKnight&>(piece)); }},
  {"NICE",  [](const Piece& piece) { return std::make_unique<IceKnight>(static_cast<const IceKnight&>(piece)); }},
  {"B",     [](const Piece& piece) { return std::make_unique<Bishop>(static_cast<const Bishop&>(piece)); }},
  {"BCLR",  [](const Piece& piece) { return std::make_unique<ColorBlindBishop>(static_cast<const ColorBlindBishop&>(piece)); }},
  {"BPRC",  [](const Piece& piece) { return std::make_unique<PreacherBishop>(static_cast<const PreacherBishop&>(piece)); }},
  {"Q",     [](const Piece& piece) { return std::make_unique<Queen>(static_cast<const Queen&>(piece)); }},
  {"QFLP",  [](const Piece& piece) { return std::make_unique<FlipperQueen>(static_cast<const FlipperQueen&>(piece)); }},
  {"QJMP",  [](const Piece& piece) { return std::make_unique<JumpyQueen>(static_cast<const JumpyQueen&>(piece)); }},
  {"QHNGR", [](const Piece& piece) { return std::make_unique<HungryQueen>(static_cast<const HungryQueen&>(piece)); }},
  {"K",     [](const Piece& piece) { return std::make_unique<King>(static_cast<const King&>(piece)); }},
  {"KFRT",  [](const Piece& piece) { return std::make_unique<FrightenedKing>(static_cast<const FrightenedKing&>(piece)); }},
  {"KARC",  [](const Piece& piece) { return std::make_unique<ArcherKing>(static_cast<const ArcherKing&>(piece)); }}
};

const std::map<std::string, std::function<std::unique_ptr<ActivePower>(const ActivePower& power)>> Utils::PIECE_ID_POWER_COPY_CONSTRUCTOR_MAPPING_
{
  {"PIPT",  [](const ActivePower& power) { return std::make_unique<ImpatientPawnPower>(static_cast<const ImpatientPawnPower&>(power)); }},
  {"PSTB",  [](const ActivePower& power) { return std::make_unique<StubbornPawnPower>(static_cast<const StubbornPawnPower&>(power)); }},
  {"PNRV",  [](const ActivePower& power) { return std::make_unique<NervousPawnPower>(static_cast<const NervousPawnPower&>(power)); }},
  {"PEXP",  [](const ActivePower& power) { return std::make_unique<ExplosivePawnPower>(static_cast<const ExplosivePawnPower&>(power)); }},
  {"RINV",  [](const ActivePower& power) { return std::make_unique<InvincibleRookPower>(static_cast<const InvincibleRookPower&>(power)); }},
  {"RPNT",  [](const ActivePower& power) { return std::make_unique<PainterRookPower>(static_cast<const PainterRookPower&>(power)); }},
  {"BCLR",  [](const ActivePower& power) { return std::make_unique<ColorBlindBishopPower>(static_cast<const ColorBlindBishopPower&>(power)); }},
  {"BPRC",  [](const ActivePower& power) { return std::make_unique<PreacherBishopPower>(static_cast<const PreacherBishopPower&>(power)); }},
  {"QFLP",  [](const ActivePower& power) { return std::make_unique<FlipperQueenPower>(static_cast<const FlipperQueenPower&>(power)); }},
  {"QJMP",  [](const ActivePower& power) { return std::make_unique<JumpyQueenPower>(static_cast<const JumpyQueenPower&>(power)); }},
  {"KARC",  [](const ActivePower& power) { return std::make_unique<ArcherKingPower>(static_cast<const ArcherKingPower&>(power)); }}
};

const std::map<std::string, std::function<std::unique_ptr<Item>()>> Utils::ITEM_ID_CONSTRUCTOR_MAPPING_
{
  {"FREEZE",  []() { return std::make_unique<FreezePotion>(); }},
  {"TP",      []() { return std::make_unique<TeleportPotion>(); }},
  {"EVENODD", []() { return std::make_unique<EvenOddPotion>(); }},
  {"LUKE",    []() { return std::make_unique<SkywalkerPotion>(); }},
  {"SHIELD",  []() { return std::make_unique<Shield>(); }},
  {"CLOAK",   []() { return std::make_unique<InvisibilityCloak>(); }},
  {"REPEL",   []() { return std::make_unique<QueenRepellant>(); }}
};

const std::map<ItemId, std::function<std::unique_ptr<Item>(const Item& item)>> Utils::ITEM_ID_COPY_CONSTRUCTOR_MAPPING_
{
  {ItemId::FREEZE,  [](const Item& item) { return std::make_unique<FreezePotion>(static_cast<const FreezePotion&>(item)); }},
  {ItemId::TP,      [](const Item& item) { return std::make_unique<TeleportPotion>(static_cast<const TeleportPotion&>(item)); }},
  {ItemId::EVENODD, [](const Item& item) { return std::make_unique<EvenOddPotion>(static_cast<const EvenOddPotion&>(item)); }},
  {ItemId::LUKE,    [](const Item& item) { return std::make_unique<SkywalkerPotion>(static_cast<const SkywalkerPotion&>(item)); }},
  {ItemId::SHIELD,  [](const Item& item) { return std::make_unique<Shield>(static_cast<const Shield&>(item)); }},
  {ItemId::CLOAK,   [](const Item& item) { return std::make_unique<InvisibilityCloak>(static_cast<const InvisibilityCloak&>(item)); }},
  {ItemId::REPEL,   [](const Item& item) { return std::make_unique<QueenRepellant>(static_cast<const QueenRepellant&>(item)); }}
};

const std::map<SquareType, std::function<Square*(const Square& square)>> Utils::SQUARE_ID_COPY_CONSTRUCTOR_MAPPING_
{
  {SquareType::BASIC_WHITE,   [](const Square& square) { return new Square(square); }},
  {SquareType::BASIC_BLACK,   [](const Square& square) { return new Square(square); }},
  {SquareType::MANA_SQUARE,   [](const Square& square) { return new ManaSquare(static_cast<const ManaSquare&>(square)); }},
  {SquareType::BOOST_SQUARE,  [](const Square& square) { return new BoostSquare(static_cast<const BoostSquare&>(square)); }},
  {SquareType::SPAWN_SQUARE,  [](const Square& square) { return new SpawnSquare(static_cast<const SpawnSquare&>(square)); }}
};

std::unique_ptr<Piece> Utils::createPiece(std::string id)
{
  return PIECE_ID_CONSTRUCTOR_MAPPING_.at(id)();
}

std::unique_ptr<Piece> Utils::copyPiece(std::string id, const Piece& piece)
{
  return PIECE_ID_COPY_CONSTRUCTOR_MAPPING_.at(id)(piece);
}

std::unique_ptr<ActivePower> Utils::copyPower(std::string id, const ActivePower& power)
{
  return PIECE_ID_POWER_COPY_CONSTRUCTOR_MAPPING_.at(id)(power);
}

std::unique_ptr<Item> Utils::createItem(std::string id)
{
  return ITEM_ID_CONSTRUCTOR_MAPPING_.at(id)();
}

std::unique_ptr<Item> Utils::copyItem(ItemId id, const Item& item)
{
  return ITEM_ID_COPY_CONSTRUCTOR_MAPPING_.at(id)(item);
}

Square* Utils::copySquare(SquareType type, const Square& square)
{
  return SQUARE_ID_COPY_CONSTRUCTOR_MAPPING_.at(type)(square);
}

bool Utils::stringToInt(const std::string &string, int &out)
{
  std::istringstream stream(string);
  stream >> out;
  return stream.eof() && !stream.fail();
}

bool Utils::stringToSizeT(const std::string &string, std::size_t &out)
{
  std::istringstream stream(string);
  stream >> out;
  return stream.eof() && !stream.fail();
}

bool Utils::stringToFloat(const std::string &string, float &out)
{
  std::istringstream stream(string);
  stream >> out;
  return stream.eof() && !stream.fail();
}

bool Utils::stringToDouble(const std::string &string, double &out)
{
  std::istringstream stream(string);
  stream >> out;
  return stream.eof() && !stream.fail();
}

void Utils::trimStart(std::string &string)
{
  std::size_t start = string.find_first_not_of(' ');
  string = start == std::string::npos ? "" : string.substr(start);
}

void Utils::trimEnd(std::string &string)
{
  std::size_t end = string.find_last_not_of(' ');
  string = end == std::string::npos ? "" : string.substr(0, end + 1);
}

void Utils::trim(std::string &string)
{
  trimStart(string);
  trimEnd(string);
}

void Utils::toLowerCase(std::string &string)
{
  std::transform(
    string.begin(),
    string.end(),
    string.begin(),
    [](unsigned char character)
    {
      return std::tolower(character);
    }
  );
}

void Utils::toUpperCase(std::string &string)
{
  std::transform(
    string.begin(),
    string.end(),
    string.begin(),
    [](unsigned char character)
    {
      return std::toupper(character);
    }
  );
}

void Utils::tokenize(const std::string &string, std::vector<std::string> &tokens, char delimiter)
{
  tokens.clear();
  
  std::size_t position = 0;
  std::size_t position_2 = 0;
  std::string token;
  while ((position_2 = string.find(delimiter, position)) != std::string::npos)
  {
    token = string.substr(position, position_2 - position);
    position = position_2 + 1;
    trim(token);
    if (!token.empty())
    {
      tokens.push_back(token);
    }
  }
  token = string.substr(position);
  trim(token);
  if (!token.empty())
  {
    tokens.push_back(token);
  }
}

void Utils::tokenizeWithoutTrimming(const std::string &string, std::vector<std::string> &tokens, char delimiter)
{
  tokens.clear();
  
  std::size_t position = 0;
  std::size_t position_2 = 0;
  std::string token;
  while ((position_2 = string.find(delimiter, position)) != std::string::npos)
  {
    token = string.substr(position, position_2 - position);
    position = position_2 + 1;
    if (!token.empty())
    {
      tokens.push_back(token);
    }
  }
  token = string.substr(position);
  if (!token.empty())
  {
    tokens.push_back(token);
  }
}
