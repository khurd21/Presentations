#ifndef PRESENTATIONS_ELEMENT_RENDERER_HPP
#define PRESENTATIONS_ELEMENT_RENDERER_HPP

#include <QWidget>

namespace presentations {
struct ParsedElement;

class ElementRenderer {
  public:
    static QWidget* render(const ParsedElement& element, QWidget* parent = nullptr);
};

} // namespace presentations

#endif // PRESENTATIONS_ELEMENT_RENDERER_HPP
