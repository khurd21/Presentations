#ifndef PRESENTATIONS_THEME_MANAGER_HPP
#define PRESENTATIONS_THEME_MANAGER_HPP

#include <QJsonObject>
#include <QObject>

#include <string>
#include <vector>

namespace presentations {

/**
 * @class ThemeManager
 * @brief The ThemeManager class is used to manage the themes.
 */
class ThemeManager final : public QObject {
    Q_OBJECT
  public:
    /**
     * @brief Construct a new ThemeManager object.
     * @param parent The parent widget.
     */
    explicit ThemeManager(QObject* parent = nullptr);

    /**
     * @brief The theme manager is a singleton. This function returns the instance of the manager.
     * @return The instance of the manager.
     */
    static ThemeManager& instance();

    /**
     * @brief Gets the list of themes.
     * @return The list of themes.
     */
    [[nodiscard]] std::vector<std::string> getThemes() const;

    /**
     * @brief Sets the theme. If no matching theme is found, a theme will not be applied.
     * @param theme The theme to set.
     */
    void setTheme(const std::string& theme);

    /**
     * @brief Gets the current theme.
     * @return The current theme.
     */
    [[nodiscard]] std::string getTheme() const;

  private slots:
    void onColorSchemeChanged(const Qt::ColorScheme& colorScheme);

  private:
    std::vector<QJsonObject> m_themeData;
    std::string m_theme;
};

} // namespace presentations

#endif // PRESENTATIONS_THEME_MANAGER_HPP
