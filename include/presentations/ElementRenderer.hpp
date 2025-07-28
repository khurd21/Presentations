#ifndef PRESENTATIONS_ELEMENT_RENDERER_HPP
#define PRESENTATIONS_ELEMENT_RENDERER_HPP

#include <QWidget>

namespace presentations {
struct ParsedElement;

/**
 * @class ElementRenderer
 * @brief The ElementRenderer class is used to render the parsed elements.
 */
class ElementRenderer {
  public:
    /**
     * @brief Render the specified element.
     * @param element The element to render.
     * @param parent The parent widget.
     * @return The rendered widget.
     */
    static QWidget* render(const ParsedElement& element, QWidget* parent = nullptr);
};

} // namespace presentations

#endif // PRESENTATIONS_ELEMENT_RENDERER_HPP
