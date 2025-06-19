#ifndef PRESENTATIONS_CODE_EDITOR_HPP
#define PRESENTATIONS_CODE_EDITOR_HPP

#include <QPlainTextEdit>

#include <string>

namespace presentations {

class CodeEditor final : public QPlainTextEdit {
    Q_OBJECT
  public:
    explicit CodeEditor(QWidget* parent = nullptr);
};

} // namespace presentations

#endif // PRESENTATIONS_CODE_EDITOR_HPP
