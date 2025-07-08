#ifndef PRESENTATIONS_CODE_THEME_CONFIG_HPP
#define PRESENTATIONS_CODE_THEME_CONFIG_HPP

#include <QFile>
#include <QJsonObject>
#include <QString>

#include <vector>

namespace presentations {

class CodeThemeConfig {
  public:
    void loadFromFile(QFile file);
    [[nodiscard]] bool isValid() const;

    [[nodiscard]] QString specialCharacterFor(const QString& type) const;
    [[nodiscard]] std::vector<std::pair<QString, QString>> specialCharacters() const;
    [[nodiscard]] QJsonObject defaultAttributesFor(const QString& type) const;
    [[nodiscard]] bool isModifierValidFor(const QString& modifier, const QString& type) const;

  private:
    void parse(const QJsonObject& json);

    QJsonObject m_specialCharacters;
    QJsonObject m_elements;
    QJsonObject m_modifiers;
    bool m_isValid{};
};

} // namespace presentations

#endif // PRESENTATIONS_CODE_THEME_CONFIG_HPP
