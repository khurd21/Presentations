#include <presentations/CodeParser.hpp>
#include <presentations/CodeThemeConfig.hpp>
#include <presentations/ParsedElement.hpp>

#include <QMap>
#include <QRegularExpression>
#include <QString>
#include <QVariant>

#include <vector>

namespace presentations {

CodeParser::CodeParser(CodeThemeConfig& config) : m_config(config) {}

std::vector<ParsedElement> CodeParser::parse(const QString& code) const {
    std::vector<ParsedElement> elements;
    const auto lines{code.split('\n')};
    QMap<QString, QVariant> activeModifiers;
    bool inModifierBlock{};
    const auto modifiersStart{m_config.specialCharacterFor("modifierStart")};
    const auto modifiersEnd{m_config.specialCharacterFor("modifierEnd")};
    for (decltype(lines.size()) i{}; i < lines.size(); ++i) {
        const auto line{lines.at(i).trimmed()};
        if (line.isEmpty()) {
            continue;
        }

        if (modifiersStart == line) {
            inModifierBlock = true;
            activeModifiers.clear();
            continue;
        }
        if (modifiersEnd == line) {
            inModifierBlock = false;
            continue;
        }

        if (inModifierBlock) {
            if (const auto parts{line.split(':', Qt::SkipEmptyParts)}; parts.size() == 2) {
                const auto key{parts.at(0).trimmed()};
                if (const auto value{parts.at(1).trimmed()}; value.contains(QRegularExpression{"^[0-9]+$"})) {
                    activeModifiers.insert(key, value.toInt());
                } else {
                    activeModifiers.insert(key, value);
                }
            }
            continue;
        }

        QString type;
        auto content{line};
        for (const auto& [candidateType, specialCharacter] : m_config.specialCharacters()) {
            if (line.startsWith(specialCharacter)) {
                type = candidateType;
                content = line.mid(specialCharacter.size()).trimmed();
                break;
            }
        }

        if (type.isEmpty()) {
            continue;
        }

        const auto defaultAttributes{m_config.defaultAttributesFor(type)};
        QMap<QString, QVariant> attributes;
        for (const auto& key : defaultAttributes.keys()) {
            if (m_config.isModifierValidFor(key, type)) {
                attributes.insert(key, activeModifiers.value(key, defaultAttributes.value(key)));
            }
        }

        elements.push_back(ParsedElement{.type = type, .content = content, .attributes = attributes, .lineNumber = static_cast<int>(i + 1)});
    }
    return elements;
}

} // namespace presentations