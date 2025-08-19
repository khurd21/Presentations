#include <presentations/CodeEditor.hpp>
#include <presentations/VimPlainTextEdit.hpp>

#include <algorithm>

#include <QApplication>
#include <QEvent>
#include <QFontDatabase>
#include <QLabel>
#include <QPlainTextEdit>
#include <QString>
#include <QTextBlock>
#include <QTextCursor>
#include <QVBoxLayout>
#include <QWidget>

namespace presentations {

CodeEditor::CodeEditor(QWidget* parent) : QWidget(parent), m_editor(new VimPlainTextEdit(this)), m_statusBarLabel(new QLabel(this)) {
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
    m_editor->setBlockCursor(m_mode == Mode::Visual || m_mode == Mode::Normal);
    updateStatusBar();
}
QString CodeEditor::toPlainText() const { return m_editor->toPlainText(); }

void CodeEditor::setPlainText(const QString& text) { m_editor->setPlainText(text); }

void CodeEditor::clear() { m_editor->clear(); }

bool CodeEditor::eventFilter(QObject* watched, QEvent* event) {
    if (watched == m_editor && event->type() == QEvent::KeyPress) {
        const auto keyEvent{dynamic_cast<QKeyEvent*>(event)};
        switch (m_mode) {
        case Mode::Normal:
            return keyEventNormalMode(keyEvent);
        case Mode::Visual:
            return keyEventVisualMode(keyEvent);
        case Mode::Insert:
            return keyEventInsertMode(keyEvent);
        default:
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

bool CodeEditor::keyEventNormalMode(QKeyEvent* event) {
    if (m_mode != Mode::Normal) {
        qWarning() << "Key event received in non-normal mode.";
        return false;
    }

    const auto cursor{m_editor->textCursor()};
    const auto position{cursor.position()};
    const auto blockStart{cursor.block().position()};
    const auto blockEnd{blockStart + cursor.block().length() - 1};

    switch (event->key()) {
    case Qt::Key_H:
    case Qt::Key_Left:
        if (position > blockStart) {
            m_editor->moveCursor(QTextCursor::Left);
        }
        break;
    case Qt::Key_L:
    case Qt::Key_Right:
        if (position < blockEnd) {
            m_editor->moveCursor(QTextCursor::Right);
        }
        break;
    case Qt::Key_J:
    case Qt::Key_Down:
        m_editor->moveCursor(QTextCursor::Down);
        break;
    case Qt::Key_K:
    case Qt::Key_Up:
        m_editor->moveCursor(QTextCursor::Up);
        break;

    case Qt::Key_I:
        setMode(Mode::Insert);
        break;

    case Qt::Key_V:
        setMode(Mode::Visual);
        break;

    default:
        break;
    }

    return true;
}

bool CodeEditor::keyEventVisualMode(QKeyEvent* event) {
    if (m_mode != Mode::Visual) {
        qWarning() << "Key event received in non-visual mode.";
        return false;
    }

    if (event->key() == Qt::Key_Escape) {
        setMode(Mode::Normal);
        auto cursor{m_editor->textCursor()};
        cursor.clearSelection();
        m_editor->setTextCursor(cursor);
        return true;
    }

    auto cursor{m_editor->textCursor()};
    const auto position{cursor.position()};
    const auto blockStart{cursor.block().position()};
    const auto blockEnd{blockStart + cursor.block().length() - 1};
    constexpr auto moveMode{QTextCursor::KeepAnchor};

    switch (event->key()) {
    case Qt::Key_H:
    case Qt::Key_Left:
        if (position > blockStart) {
            cursor.movePosition(QTextCursor::Left, moveMode);
        }
        break;
    case Qt::Key_L:
    case Qt::Key_Right:
        if (position < blockEnd) {
            cursor.movePosition(QTextCursor::Right, moveMode);
        }
        break;
    case Qt::Key_J:
    case Qt::Key_Down:
        cursor.movePosition(QTextCursor::Down, moveMode);
        break;
    case Qt::Key_K:
    case Qt::Key_Up:
        cursor.movePosition(QTextCursor::Up, moveMode);
        break;
    default:
        break;
    }

    m_editor->setTextCursor(cursor);
    return true;
}

bool CodeEditor::keyEventInsertMode(QKeyEvent* event) {
    if (m_mode != Mode::Insert) {
        qWarning() << "Key event received in non-insert mode.";
        return false;
    }

    if (event->key() == Qt::Key_Escape) {
        setMode(Mode::Normal);
        return true;
    }

    return false;
}

} // namespace presentations