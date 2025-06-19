#ifndef PRESENTATIONS_PARSED_ELEMENT_HPP
#define PRESENTATIONS_PARSED_ELEMENT_HPP

#include <QMap>
#include <QString>
#include <QVariant>

namespace presentations {

struct ParsedElement {
    QString type;
    QString content;
    QMap<QString, QVariant> attributes;
    int lineNumber{};
};

} // namespace presentations

#endif // PRESENTATIONS_PARSED_ELEMENT_HPP
