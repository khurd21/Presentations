#include "presentations/ThemeManager.hpp"

#include <QGuiApplication>
#include <presentations/SlidePreviewDelegate.hpp>
#include <presentations/SlidePreviewListView.hpp>

#include <QApplication>
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

void SlidePreviewListView::addSlide(const int number, QWidget* previewWidget) {
    const auto item{new QStandardItem()};
    item->setData(number, SlideNumberRole);
    item->setData(QVariant::fromValue(QPointer(previewWidget)), WidgetTypeRole);
    m_model.appendRow(item);
    setCurrentSlide(m_model.rowCount() - 1);
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