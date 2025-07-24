#include "presentations/ThemeManager.hpp"

#include <QGuiApplication>
#include <presentations/SlidePreviewDelegate.hpp>
#include <presentations/SlidePreviewListView.hpp>

#include <QApplication>
#include <QKeySequence>
#include <QPointer>
#include <QScroller>
#include <QStandardItem>
#include <QStyleHints>
#include <QWheelEvent>
#include <QWidget>

namespace presentations {

SlidePreviewListView::SlidePreviewListView(QWidget* parent) : QListView(parent) {
    QListView::setModel(&m_model);
    setItemDelegate(new SlidePreviewDelegate(this));
    setFrameShape(NoFrame);
    setBackgroundRole(QPalette::Base);
    setAutoFillBackground(true);
    connect(QGuiApplication::styleHints(), &QStyleHints::colorSchemeChanged, this, [this] { setPalette(QApplication::palette()); });
}

void SlidePreviewListView::addSlide(QWidget* previewWidget) {
    const auto item{new QStandardItem()};
    item->setData(m_model.rowCount() + 1, SlideNumberRole);
    item->setData(QVariant::fromValue(QPointer(previewWidget)), WidgetTypeRole);
    m_model.appendRow(item);
    setCurrentSlide(m_model.rowCount() - 1);
}

void SlidePreviewListView::removeSlide(int index) {
    if (index >= 0 && index < m_model.rowCount()) {
        m_model.removeRow(index);
    }

    for (int i{}; i < m_model.rowCount(); ++i) {
        m_model.item(i, 0)->setData(i + 1, SlideNumberRole);
    }
    index -= static_cast<int>(m_model.rowCount() == index);
    if (index >= 0) {
        setCurrentSlide(index);
    }
    viewport()->update();
}

void SlidePreviewListView::keyPressEvent(QKeyEvent* event) {
    const auto pressedKey{static_cast<QKeySequence>(event->key() | event->modifiers())};
    // Delete Request
    if (pressedKey.matches(QKeySequence::Delete) || (event->modifiers() == Qt::ControlModifier && event->key() == Qt::Key_D)) {
        if (const auto selectedIndexes{selectionModel()->selectedIndexes()}; !selectedIndexes.isEmpty()) {
            if (const auto index{selectedIndexes.first()}; index.isValid() && index.row() >= 0 && index.row() < m_model.rowCount()) {
                emit slideDeleteRequested(index.row());
            }
        }
        event->accept();
        return;
    }
    // New Slide Request
    if (pressedKey.matches(QKeySequence::New) || (event->modifiers() == Qt::ControlModifier && event->key() == Qt::Key_N)) {
        emit slideCreateRequested();
        event->accept();
        return;
    }
    QListView::keyPressEvent(event);
}

void SlidePreviewListView::setCurrentSlide(const int index) {
    if (index >= 0 && index < m_model.rowCount()) {
        const auto& modelIndex{m_model.index(index, 0)};
        selectionModel()->select(modelIndex, QItemSelectionModel::ClearAndSelect);
        scrollTo(modelIndex);
        emit clicked(modelIndex);
    }
}

void SlidePreviewListView::handleCanvasUpdate(const int index) {
    if (index >= 0 && index < m_model.rowCount()) {
        update(m_model.index(index, 0));
    }
}

} // namespace presentations