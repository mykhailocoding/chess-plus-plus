//----------------------------------------------------------------------------------------------------------------------
/// The Utils class contains some useful functions for use in other classes. These include type conversions, 
/// trimming input, converting the case of strings as well as splitting a string into tokens.
///
/// Author(s): Tutors
///
/// we added a function to tokenize a string without trimming and to create/copy objects
//----------------------------------------------------------------------------------------------------------------------
#ifndef UTILS_HPP
#define UTILS_HPP

#include <algorithm>
#include <sstream>
#include <string>
#include <vector>
#include <format>
#include <map>
#include <memory>
#include <functional>

// forward declarations
class Piece;
class ActivePower;
class Item;
enum class ItemId;
class Square;
enum class SquareType;

class Utils
{
  private:
    static const std::map<std::string, std::function<std::unique_ptr<Piece>()>> PIECE_ID_CONSTRUCTOR_MAPPING_;
    static const std::map<std::string, std::function<std::unique_ptr<Piece>(const Piece& piece)>> PIECE_ID_COPY_CONSTRUCTOR_MAPPING_;
    static const std::map<std::string, std::function<std::unique_ptr<ActivePower>(const ActivePower& power)>> PIECE_ID_POWER_COPY_CONSTRUCTOR_MAPPING_;
    static const std::map<std::string, std::function<std::unique_ptr<Item>()>> ITEM_ID_CONSTRUCTOR_MAPPING_;
    static const std::map<ItemId, std::function<std::unique_ptr<Item>(const Item& item)>> ITEM_ID_COPY_CONSTRUCTOR_MAPPING_;
    static const std::map<SquareType, std::function<Square*(const Square& square)>> SQUARE_ID_COPY_CONSTRUCTOR_MAPPING_;

  public:
    //------------------------------------------------------------------------------------------------------------------
    /// @brief Constructor is deleted explicitly.
    Utils() = delete;

    //------------------------------------------------------------------------------------------------------------------
    /// @brief Copy constructor is deleted explicitly.
    Utils(const Utils &) = delete;

    //------------------------------------------------------------------------------------------------------------------
    /// @brief Destructor is deleted explicitly.
    virtual ~Utils() = delete;

    //------------------------------------------------------------------------------------------------------------------
    /// @brief Creates piece by specified id using map.
    /// @param id id of the piece
    /// @return unique pointer to the created piece
    static std::unique_ptr<Piece> createPiece(std::string id);

    //------------------------------------------------------------------------------------------------------------------
    /// @brief Copies piece with the map using piece object and id as references.
    /// @param id id of the piece
    /// @param piece piece object to copy
    /// @return unique pointer to the copied piece
    static std::unique_ptr<Piece> copyPiece(std::string id, const Piece& piece);

    //------------------------------------------------------------------------------------------------------------------
    /// @brief Copies power with the map using power object and id as references.
    /// @param id id of the power
    /// @param piece power object to copy
    /// @return unique pointer to the copied power
    static std::unique_ptr<ActivePower> copyPower(std::string id, const ActivePower& power);

    //------------------------------------------------------------------------------------------------------------------
    /// @brief Creates item by specified id using map.
    /// @param id id of the item
    /// @return unique pointer to the created item
    static std::unique_ptr<Item> createItem(std::string id);

    //------------------------------------------------------------------------------------------------------------------
    /// @brief Copies item with the map using item object and id as references.
    /// @param id id of the itme
    /// @param piece item object to copy
    /// @return unique pointer to the copied item
    static std::unique_ptr<Item> copyItem(ItemId id, const Item& item);

    //------------------------------------------------------------------------------------------------------------------
    /// @brief Copies square with the map using square object and id as references.
    /// @param id id of the square
    /// @param piece square object to copy
    /// @return unique pointer to the copied square
    static Square* copySquare(SquareType type, const Square& square);

    //------------------------------------------------------------------------------------------------------------------
    /// @brief This function converts a string into an int. The conversion is only successful, if all
    ///        elements of the string are converted.
    /// @param string string that should be converted
    /// @param out the converted int
    /// @return true, if conversion was successful, false otherwise
    static bool stringToInt(const std::string &string, int &out);

    //------------------------------------------------------------------------------------------------------------------
    /// @brief This function converts a string into an std::size_t. The conversion is only successful, if all
    ///        elements of the string are converted.
    /// @param string string that should be converted
    /// @param out the converted std::size_t
    /// @return true, if conversion was successful, false otherwise
    static bool stringToSizeT(const std::string &string, std::size_t &out);

    //------------------------------------------------------------------------------------------------------------------
    /// @brief This function converts a string into a float. The conversion is only successful, if all
    ///        elements of the string are converted.
    /// @param string string that should be converted
    /// @param out the converted float
    /// @return true, if conversion was successful, false otherwise
    static bool stringToFloat(const std::string &string, float &out);

    //------------------------------------------------------------------------------------------------------------------
    /// @brief This function converts a string into a double. The conversion is only successful, if all
    ///        elements of the string are converted.
    /// @param string string that should be converted
    /// @param out the converted double
    /// @return true, if conversion was successful, false otherwise
    static bool stringToDouble(const std::string &string, double &out);

    //------------------------------------------------------------------------------------------------------------------
    /// @brief This function removes leading whitespaces from a string.
    /// @param string the string to remove leading whitespaces from
    static void trimStart(std::string &string);

    //------------------------------------------------------------------------------------------------------------------
    /// @brief This function removes trailing whitespaces from a string.
    /// @param string the string to remove trailing whitespaces from
    static void trimEnd(std::string &string);

    //------------------------------------------------------------------------------------------------------------------
    /// @brief This function removes trailing and leading whitespaces from a string.
    /// @param string the string to remove whitespaces from
    static void trim(std::string &string);

    //------------------------------------------------------------------------------------------------------------------
    /// @brief This function converts a string to lower case.
    /// @param string the string to convert
    static void toLowerCase(std::string &string);

    //------------------------------------------------------------------------------------------------------------------
    /// @brief This function converts a string to upper case.
    /// @param string the string to convert
    static void toUpperCase(std::string &string);

    //------------------------------------------------------------------------------------------------------------------
    /// @brief This function splits a string into tokens using a delimiter and stores the tokens in a vector.
    /// @param string the string to split
    /// @param tokens the vector to store the tokens in
    /// @param delimiter delimiter to use for splitting
    static void tokenize(const std::string &string, std::vector<std::string> &tokens, char delimiter);

    /// @brief  splits a string into individual tokens based on a delimiter
    /// @param string the string to be tokenized
    /// @param tokens the vector where the tokenized string will be stored
    /// @param delimiter the character used as a seperator 
    static void tokenizeWithoutTrimming(const std::string &string, std::vector<std::string> &tokens, char delimiter);
};

#endif // UTILS_HPP
