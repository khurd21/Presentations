#include <presentations/VimPlainTextEdit.hpp>

#include <QPaintEvent>
#include <QPainter>
#include <QRect>

namespace presentations {

VimPlainTextEdit::VimPlainTextEdit(QWidget* parent) {}

void VimPlainTextEdit::setBlockCursor(const bool enabled) {
    if (m_blockCursor == enabled) {
        return;
    }
    m_blockCursor = enabled;
    viewport()->update();
}

void VimPlainTextEdit::paintEvent(QPaintEvent* event) {
    QPlainTextEdit::paintEvent(event);

    if (m_blockCursor && !isReadOnly()) {
        const auto cursor{textCursor()};
        const auto rect{cursorRect(cursor)};
        if (rect.isValid()) {
            QPainter painter(viewport());
            auto color{palette().highlight().color()};
            color.setAlpha(128);
            painter.fillRect(rect, color);
        }
    }
}

} // namespace presentations