#ifndef PRESENTATIONS_SPECIAL_CHARACTERS_HPP
#define PRESENTATIONS_SPECIAL_CHARACTERS_HPP

#include <QString>

namespace presentations {

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

SpecialCharacterType fromString(const QString& type);
QString toString(const SpecialCharacterType& type);

struct SpecialCharacter {
    SpecialCharacterType type;
    QString specialCharacter;
};

} // namespace presentations

#endif // PRESENTATIONS_SPECIAL_CHARACTERS_HPP
