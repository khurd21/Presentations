#ifndef PRESENTATIONS_SPECIAL_CHARACTERS_HPP
#define PRESENTATIONS_SPECIAL_CHARACTERS_HPP

#include <QString>

namespace presentations {

/**
 * @enum SpecialCharacterType
 * @brief The SpecialCharacterType enum is used to identify the special character type.
 */
enum class SpecialCharacterType {
    Unknown,
    Title,
    SubTitle,
    SubSubTitle,
    ModifiersStart,
    ModifiersEnd,
    BulletPoint,
    Text,
};

/**
 * @struct SpecialCharacter
 * @brief The SpecialCharacter struct is used to store the special character type and the corresponding string.
 */
struct SpecialCharacter {
    SpecialCharacterType type;
    QString specialCharacter;
};

/**
 * @brief Converts the specified string to the corresponding SpecialCharacterType.
 * @param type The string to convert.
 * @return The corresponding SpecialCharacterType.
 */
SpecialCharacterType fromString(const QString& type);

/**
 * @brief Converts the specified SpecialCharacterType to a string.
 * @param type The type to convert.
 * @return The corresponding string.
 */
QString toString(const SpecialCharacterType& type);

} // namespace presentations

#endif // PRESENTATIONS_SPECIAL_CHARACTERS_HPP
