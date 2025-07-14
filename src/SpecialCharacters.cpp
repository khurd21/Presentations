#include <presentations/SpecialCharacters.hpp>

#include <QString>

#include <string>
#include <unordered_map>

namespace presentations {

SpecialCharacterType fromString(const QString& type) {
    using CT = SpecialCharacterType;
    static const std::unordered_map<std::string, SpecialCharacterType> fromStringMap{
        {"title", CT::Title},
        {"subtitle", CT::SubTitle},
        {"subsubtitle", CT::SubSubTitle},
        {"modifiersStart", CT::ModifiersStart},
        {"modifiersEnd", CT::ModifiersEnd},
        {"bulletPoint", CT::BulletPoint},
        {"text", CT::Text},
    };

    if (!fromStringMap.contains(type.toStdString())) {
        return CT::Unknown;
    }
    return fromStringMap.at(type.toStdString());
}

QString toString(const SpecialCharacterType& type) {
    using CT = SpecialCharacterType;
    static const std::unordered_map<SpecialCharacterType, std::string> toStringMap{
        {CT::Title, "title"},
        {CT::SubTitle, "subtitle"},
        {CT::SubSubTitle, "subsubtitle"},
        {CT::ModifiersStart, "modifiersStart"},
        {CT::ModifiersEnd, "modifiersEnd"},
        {CT::BulletPoint, "bulletPoint"},
        {CT::Text, "text"},
    };

    if (!toStringMap.contains(type)) {
        return "Unknown";
    }
    return QString::fromStdString(toStringMap.at(type));
}

} // namespace presentations