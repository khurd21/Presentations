#ifndef PRESENTATIONS_CODE_EDITOR_HPP
#define PRESENTATIONS_CODE_EDITOR_HPP

#include <QPlainTextEdit>

namespace presentations {

/**
 * @class CodeEditor
 * @brief The CodeEditor class is a simple text editor for code. The content of the
 * code editor is used to render the slide content.
 */
class CodeEditor final : public QPlainTextEdit {
    Q_OBJECT
  public:
    /**
     * @brief Construct a new CodeEditor object.
     * @param parent The parent widget.
     */
    explicit CodeEditor(QWidget* parent = nullptr);
};

} // namespace presentations

#endif // PRESENTATIONS_CODE_EDITOR_HPP
