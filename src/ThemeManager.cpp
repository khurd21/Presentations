#include <QApplication>
#include <presentations/ThemeManager.hpp>

#include <QApplication>
#include <QDir>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonParseError>
#include <QPalette>

#include <array>
#include <stdexcept>
#include <string>
#include <vector>

namespace {

bool isValidTheme(const QJsonObject& object) {
    constexpr std::array requiredKeys{"name", "palette"};
    for (const auto& key : requiredKeys) {
        if (!object.contains(key)) {
            return false;
        }
    }
    if (!object["name"].isString()) {
        return false;
    }
    if (object["name"].toString().isEmpty()) {
        return false;
    }

    const auto palette{object["palette"].toObject()};
    constexpr std::array requiredPaletteKeys{
        "window", "windowText", "base", "alternateBase", "text", "button", "buttonText", "highlight", "highlightedText", "toolTipBase", "toolTipText",
    };
    for (const auto& key : requiredPaletteKeys) {
        if (!palette.contains(key)) {
            return false;
        }
    }
    return true;
}

std::vector<QJsonObject> findThemes() {
    std::vector<QJsonObject> themes;
    QFile themesFile{":/themes/themes.json"};
    if (!themesFile.open(QIODeviceBase::ReadOnly)) {
        return themes;
    }

    QJsonParseError error;
    const auto json{QJsonDocument::fromJson(themesFile.readAll(), &error)};
    if (error.error != QJsonParseError::NoError || !json.isArray()) {
        return themes;
    }

    for (const auto& theme : json.array()) {
        if (isValidTheme(theme.toObject())) {
            themes.push_back(theme.toObject());
        }
    }
    return themes;
}

QPalette applyTheme(const QJsonObject& theme) {
    if (!isValidTheme(theme)) {
        throw std::runtime_error("Invalid theme.");
    }

    const auto paletteObj{theme["palette"].toObject()};
    const auto getColor = [](const auto& obj, const auto& key) -> QColor {
        const auto value = obj[key].toString();
        if (const QColor color{value}; color.isValid()) {
            return color;
        }
        qWarning() << "Invalid color for key" << key << ":" << value;
        return {};
    };

    QPalette palette;
    palette.setColor(QPalette::Window, getColor(paletteObj, "window"));
    palette.setColor(QPalette::WindowText, getColor(paletteObj, "windowText"));
    palette.setColor(QPalette::Base, getColor(paletteObj, "base"));
    palette.setColor(QPalette::AlternateBase, getColor(paletteObj, "alternateBase"));
    palette.setColor(QPalette::Text, getColor(paletteObj, "text"));
    palette.setColor(QPalette::Button, getColor(paletteObj, "button"));
    palette.setColor(QPalette::ButtonText, getColor(paletteObj, "buttonText"));
    palette.setColor(QPalette::Highlight, getColor(paletteObj, "highlight"));
    palette.setColor(QPalette::HighlightedText, getColor(paletteObj, "highlightedText"));
    palette.setColor(QPalette::ToolTipBase, getColor(paletteObj, "toolTipBase"));
    palette.setColor(QPalette::ToolTipText, getColor(paletteObj, "toolTipText"));
    QApplication::setPalette(palette);

    qDebug() << "Window: " << palette.color(QPalette::Window).name();
    qDebug() << "WindowText: " << palette.color(QPalette::WindowText).name();
    qDebug() << "Base: " << palette.color(QPalette::Base).name();
    qDebug() << "AlternateBase: " << palette.color(QPalette::AlternateBase).name();
    qDebug() << "Text: " << palette.color(QPalette::Text).name();
    qDebug() << "Button: " << palette.color(QPalette::Button).name();
    qDebug() << "ButtonText: " << palette.color(QPalette::ButtonText).name();
    qDebug() << "Highlight: " << palette.color(QPalette::Highlight).name();
    qDebug() << "HighlightedText: " << palette.color(QPalette::HighlightedText).name();
    qDebug() << "ToolTipBase: " << palette.color(QPalette::ToolTipBase).name();
    qDebug() << "ToolTipText: " << palette.color(QPalette::ToolTipText).name();
    return palette;
}

} // namespace

namespace presentations {

ThemeManager::ThemeManager(QObject* parent) : QObject(parent), m_themeData(findThemes()) {
    if (!m_themeData.empty()) {
        m_theme = m_themeData[0]["name"].toString().toStdString();
        setTheme(m_theme);
    }
}

ThemeManager& ThemeManager::instance() {
    static ThemeManager instance;
    return instance;
}

std::vector<std::string> ThemeManager::getThemes() const {
    std::vector<std::string> themes;
    for (const auto& theme : m_themeData) {
        themes.push_back(theme["name"].toString().toStdString());
    }
    return themes;
}

void ThemeManager::setTheme(const std::string& theme) {
    for (const auto& themeData : m_themeData) {
        if (themeData["name"].toString().toStdString() == theme) {
            m_theme = theme;
            std::ignore = applyTheme(themeData);
        }
    }
}

std::string ThemeManager::getTheme() const { return m_theme; }

} // namespace presentations