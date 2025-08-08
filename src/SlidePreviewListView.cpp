#include <presentations/ShortcutManager.hpp>
#include <presentations/ShortcutRequest.hpp>
#include <presentations/SlidePreviewDelegate.hpp>
#include <presentations/SlidePreviewListView.hpp>

#include <QApplication>
#include <QPointer>
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
    connect(&ShortcutManager::instance(), &ShortcutManager::shortcutTriggered, this, &SlidePreviewListView::onShortcutTriggered);
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

void SlidePreviewListView::onShortcutTriggered(const ShortcutRequest shortcut) {

    if (shortcut == ShortcutRequest::DeleteCurrentSlidePage) {
        if (const auto selectedIndexes{selectionModel()->selectedIndexes()}; !selectedIndexes.isEmpty()) {
            if (const auto index{selectedIndexes.first()}; index.isValid() && index.row() >= 0 && index.row() < m_model.rowCount()) {
                emit slideDeleteRequested(index.row());
            }
        }
    }

    if (shortcut == ShortcutRequest::CreateNewSlidePage) {
        emit slideCreateRequested();
    }

    if (shortcut == ShortcutRequest::PreviousSlide) {
        if (selectionModel()) {
            if (const auto currentIndex{selectionModel()->currentIndex()}; currentIndex.isValid()) {
                const auto currentRow{currentIndex.row()};
                const auto newRow{currentRow > 0 ? currentRow - 1 : m_model.rowCount() - 1};
                setCurrentSlide(newRow);
            }
        }
    }

    if (shortcut == ShortcutRequest::NextSlide) {
        if (selectionModel()) {
            if (const auto currentIndex{selectionModel()->currentIndex()}; currentIndex.isValid()) {
                const auto currentRow{currentIndex.row()};
                const auto newRow{(currentRow + 1) % m_model.rowCount()};
                setCurrentSlide(newRow);
            }
        }
    }
}

void SlidePreviewListView::setCurrentSlide(const int index) {
    if (index >= 0 && index < m_model.rowCount()) {
        const auto& modelIndex{m_model.index(index, 0)};
        selectionModel()->select(modelIndex, QItemSelectionModel::ClearAndSelect);
        selectionModel()->setCurrentIndex(modelIndex, QItemSelectionModel::ClearAndSelect);
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