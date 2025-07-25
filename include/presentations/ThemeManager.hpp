#ifndef PRESENTATIONS_THEME_MANAGER_HPP
#define PRESENTATIONS_THEME_MANAGER_HPP

#include <QJsonObject>
#include <QObject>

#include <string>
#include <vector>

namespace presentations {

class ThemeManager final : public QObject {
    Q_OBJECT
  public:
    explicit ThemeManager(QObject* parent = nullptr);
    static ThemeManager& instance();

    [[nodiscard]] std::vector<std::string> getThemes() const;
    void setTheme(const std::string& theme);
    [[nodiscard]] std::string getTheme() const;

  private slots:
    void onColorSchemeChanged(const Qt::ColorScheme& colorScheme);

  private:
    std::vector<QJsonObject> m_themeData;
    std::string m_theme;
};

} // namespace presentations

#endif // PRESENTATIONS_THEME_MANAGER_HPP
