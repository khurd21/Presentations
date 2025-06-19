#include <presentations/CodeThemeConfig.hpp>

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

QString CodeThemeConfig::specialCharacterFor(const QString& type) const {
    if (m_specialCharacters.contains(type)) {
        return m_specialCharacters[type].toString();
    }
    return {};
}

std::vector<std::pair<QString, QString>> CodeThemeConfig::specialCharacters() const {
    std::vector<std::pair<QString, QString>> characters;
    for (const auto& key : m_specialCharacters.keys()) {
        characters.push_back({key, m_specialCharacters[key].toString()});
    }
    return characters;
}

QJsonObject CodeThemeConfig::defaultAttributesFor(const QString& type) const {
    if (m_elements.contains(type)) {
        return m_elements[type].toObject();
    }
    return {};
}

bool CodeThemeConfig::isModifierValidFor(const QString& modifier, const QString& type) const {
    if (m_modifiers.contains(modifier)) {
        if (const auto appliesTo{m_modifiers[modifier]["appliesTo"].toArray()}; appliesTo.contains(type)) {
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