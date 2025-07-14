#include <presentations/CodeThemeConfig.hpp>
#include <presentations/SpecialCharacters.hpp>

#include <QDebug>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>

#include <array>

namespace presentations {

void CodeThemeConfig::loadFromFile(QFile file) {
    if (!file.open(QIODevice::ReadOnly)) {
        m_isValid = false;
        qWarning() << "Failed to open code theme file: " << file.errorString();
        return;
    }
    parse(QJsonDocument::fromJson(file.readAll()).object());
}

bool CodeThemeConfig::isValid() const { return m_isValid; }

QString CodeThemeConfig::specialCharacterFor(const SpecialCharacterType& type) const {
    if (m_specialCharacters.contains(toString(type))) {
        return m_specialCharacters[toString(type)].toString();
    }
    return {};
}

std::vector<SpecialCharacter> CodeThemeConfig::specialCharacters() const {
    // TODO: It looks like fromString() is not converting correctly? Are they the values?
    std::vector<SpecialCharacter> characters;
    for (const auto& key : m_specialCharacters.keys()) {
        characters.emplace_back(SpecialCharacter{.type = fromString(key), .specialCharacter = m_specialCharacters[key].toString()});
    }
    return characters;
}

QJsonObject CodeThemeConfig::defaultAttributesFor(const SpecialCharacterType& type) const {
    if (m_elements.contains(toString(type))) {
        return m_elements[toString(type)].toObject();
    }
    return {};
}

bool CodeThemeConfig::isModifierValidFor(const QString& modifier, const SpecialCharacterType& type) const {
    if (m_modifiers.contains(modifier)) {
        if (const auto appliesTo{m_modifiers[modifier]["appliesTo"].toArray()}; appliesTo.contains(toString(type))) {
            return true;
        }
    }
    return false;
}

void CodeThemeConfig::parse(const QJsonObject& json) {
    constexpr std::array requiredKeys{"specialCharacters", "elements", "modifiers"};
    for (const auto& key : requiredKeys) {
        if (!json.contains(key)) {
            m_isValid = false;
            qWarning() << "Code theme file is missing required key:" << key;
            return;
        }
    }

    m_specialCharacters = json["specialCharacters"].toObject();
    m_elements = json["elements"].toObject();
    m_modifiers = json["modifiers"].toObject();
    m_isValid = true;
}

} // namespace presentations