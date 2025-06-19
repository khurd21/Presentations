#include <presentations/CodeEditor.hpp>

#include <QFontDatabase>
#include <QPlainTextEdit>

namespace presentations {

CodeEditor::CodeEditor(QWidget* parent) : QPlainTextEdit(parent) { setFont(QFontDatabase::systemFont(QFontDatabase::FixedFont)); }

} // namespace presentations