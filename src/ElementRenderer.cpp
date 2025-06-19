#include <presentations/ElementRenderer.hpp>
#include <presentations/ParsedElement.hpp>

#include <QHBoxLayout>
#include <QLabel>
#include <QWidget>

#include <array>
#include <unordered_map>

namespace {

QWidget* renderTextElement(const presentations::ParsedElement& element, QWidget* parent) {
    const auto label{new QLabel(parent)};
    auto content{element.content};

    // TODO: Add new widget or something for `-`
    if ("bulletPoint" == element.type) {
        content = "• " + content;
    }

    // TODO: Make this configurable
    auto palette{label->palette()};
    palette.setColor(QPalette::WindowText, Qt::black);
    label->setPalette(palette);

    label->setText(content);
    label->setWordWrap(true);
    auto font{label->font()};
    if (element.attributes.contains("font-size")) {
        font.setPointSize(element.attributes["font-size"].toInt());
    }
    if (element.attributes.contains("font-weight")) {
        const std::unordered_map<QString, QFont::Weight> weightMap{
            {"bold", QFont::Bold},
            {"normal", QFont::Normal},
        };
        if (const auto fontWeightKey{element.attributes["font-weight"].toString()}; weightMap.contains(fontWeightKey)) {
            font.setWeight(weightMap.at(fontWeightKey));
        }
    }
    label->setFont(font);

    const std::unordered_map<QString, Qt::AlignmentFlag> alignmentMap{
        {"left", Qt::AlignLeft},
        {"center", Qt::AlignHCenter},
        {"right", Qt::AlignRight},
    };
    if (element.attributes.contains("text-align")) {
        if (const auto alignmentKey{element.attributes["text-align"].toString()}; alignmentMap.contains(alignmentKey)) {
            label->setAlignment(alignmentMap.at(alignmentKey));
        }
    }

    const auto wrapper{new QWidget(parent)};
    const auto layout{new QHBoxLayout(wrapper)};
    layout->setContentsMargins(0, 0, 0, 0);
    layout->addWidget(label);
    layout->setAlignment(label->alignment());
    return wrapper;
}

} // namespace

namespace presentations {

QWidget* ElementRenderer::render(const ParsedElement& element, QWidget* parent) {
    constexpr std::array textElementTypes{"title", "subtitle", "subsubtitle", "bulletPoint", "text"};
    for (const auto& type : textElementTypes) {
        if (type == element.type) {
            return renderTextElement(element, parent);
        }
    }
    return {};
}

} // namespace presentations