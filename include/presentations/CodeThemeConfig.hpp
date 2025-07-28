#ifndef PRESENTATIONS_CODE_THEME_CONFIG_HPP
#define PRESENTATIONS_CODE_THEME_CONFIG_HPP

#include <QFile>
#include <QJsonObject>
#include <QString>

#include <vector>

namespace presentations {

enum class SpecialCharacterType;
struct SpecialCharacter;

/**
 * @class CodeThemeConfig
 * @brief
 * The CodeThemeConfig class is used to load the code theme configuration. The default
 * configuration is loaded from the default code theme file. The configuration can be
 * overridden by a custom configuration file.
 *
 * For reference, please see the default code theme file: resources/codeEditorDefaults.json
 */
class CodeThemeConfig {
  public:
    /**
     * @brief Load the code theme configuration from the specified file.
     * @param file The file to load the configuration from.
     */
    void loadFromFile(QFile file);

    /**
     * @brief Checks if the configuration is valid.
     * @return True if the configuration is valid. False otherwise.
     */
    [[nodiscard]] bool isValid() const;

    /**
     * @brief Gets the special character for the specified type.
     * @param type The type of the special character.
     * @return The special character.
     */
    [[nodiscard]] QString specialCharacterFor(const SpecialCharacterType& type) const;

    /**
     * @brief Gets the list of all special characters presently defined in the configuration file.
     * @return The list of special characters.
     */
    [[nodiscard]] std::vector<SpecialCharacter> specialCharacters() const;

    /**
     * @brief Gets the default attributes for the specified type.
     * @param type The type of the special character.
     * @return The default attributes.
     */
    [[nodiscard]] QJsonObject defaultAttributesFor(const SpecialCharacterType& type) const;

    /**
     * @brief Checks if the specified modifier is valid for the specified type.
     * @param modifier The modifier to check.
     * @param type The type of the special character.
     * @return True if the modifier is valid. False otherwise.
     */
    [[nodiscard]] bool isModifierValidFor(const QString& modifier, const SpecialCharacterType& type) const;

  private:
    void parse(const QJsonObject& json);

    QJsonObject m_specialCharacters;
    QJsonObject m_elements;
    QJsonObject m_modifiers;
    bool m_isValid{};
};

} // namespace presentations

#endif // PRESENTATIONS_CODE_THEME_CONFIG_HPP
