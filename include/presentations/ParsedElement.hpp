#ifndef PRESENTATIONS_PARSED_ELEMENT_HPP
#define PRESENTATIONS_PARSED_ELEMENT_HPP

#include <presentations/SpecialCharacters.hpp>

#include <QMap>
#include <QString>
#include <QVariant>

namespace presentations {

/**
 * @struct ParsedElement
 * @brief A decomposed section of the slide content from the code editor.
 */
struct ParsedElement {
    SpecialCharacterType type;
    QString content;
    QMap<QString, QVariant> attributes;
    int lineNumber{};
};

} // namespace presentations

#endif // PRESENTATIONS_PARSED_ELEMENT_HPP
