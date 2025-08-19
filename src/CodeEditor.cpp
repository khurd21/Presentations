#include <presentations/CodeEditor.hpp>

#include <QEvent>
#include <QFontDatabase>
#include <QLabel>
#include <QPlainTextEdit>
#include <QString>
#include <QTextCursor>
#include <QVBoxLayout>
#include <QWidget>

namespace presentations {

CodeEditor::CodeEditor(QWidget* parent) : QWidget(parent), m_editor(new QPlainTextEdit(this)), m_statusBarLabel(new QLabel(this)) {
    m_editor->setLineWrapMode(QPlainTextEdit::NoWrap);
    m_statusBarLabel->setAutoFillBackground(true);
    setFont(QFontDatabase::systemFont(QFontDatabase::FixedFont));
    setMode(Mode::Normal);

    const auto layout{new QVBoxLayout(this)};
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);
    layout->addWidget(m_editor);
    layout->addWidget(m_statusBarLabel);

    m_statusBarLabel->setFixedHeight(m_editor->fontMetrics().height() * 2);
    m_editor->installEventFilter(this);

    connect(m_editor, &QPlainTextEdit::textChanged, this, &CodeEditor::textChanged);
}

void CodeEditor::setMode(const Mode mode) {
    m_mode = mode;
    updateStatusBar();
}
QString CodeEditor::toPlainText() const { return m_editor->toPlainText(); }

void CodeEditor::setPlainText(const QString& text) { m_editor->setPlainText(text); }

void CodeEditor::clear() { m_editor->clear(); }

bool CodeEditor::eventFilter(QObject* watched, QEvent* event) {
    if (watched == m_editor && event->type() == QEvent::KeyPress) {
        const auto keyEvent{dynamic_cast<QKeyEvent*>(event)};
        if (m_mode == Mode::Normal) {
            switch (keyEvent->key()) {
            case Qt::Key_Left:
            case Qt::Key_Right:
            case Qt::Key_Up:
            case Qt::Key_Down:
            case Qt::Key_Home:
            case Qt::Key_End:
            case Qt::Key_PageUp:
            case Qt::Key_PageDown:
            case Qt::Key_Control:
            case Qt::Key_Shift:
            case Qt::Key_Alt:
                return false;

            case Qt::Key_H:
                m_editor->moveCursor(QTextCursor::Left);
                return true;
            case Qt::Key_L:
                m_editor->moveCursor(QTextCursor::Right);
                return true;
            case Qt::Key_J:
                m_editor->moveCursor(QTextCursor::Down);
                return true;
            case Qt::Key_K:
                m_editor->moveCursor(QTextCursor::Up);
                return true;

            case Qt::Key_I:
                setMode(Mode::Insert);
                return true;
            case Qt::Key_V:
                setMode(Mode::Visual);
                return true;

            default:
                return true;
            }
        }
        if (m_mode == Mode::Insert || m_mode == Mode::Visual) {
            if (keyEvent->key() == Qt::Key_Escape) {
                setMode(Mode::Normal);
                return true;
            }
            return false;
        }
    }
    return QWidget::eventFilter(watched, event);
}

void CodeEditor::updateStatusBar() const {
    const std::unordered_map<Mode, QString> modeToText{
        {Mode::Normal, "-- NORMAL --"},
        {Mode::Insert, "-- INSERT --"},
        {Mode::Visual, "-- VISUAL --"},
    };
    m_statusBarLabel->setText({});
    if (modeToText.contains(m_mode)) {
        m_statusBarLabel->setText(modeToText.at(m_mode));
    }
}

} // namespace presentations