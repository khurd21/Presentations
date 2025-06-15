#include <presentations/SlidePreviewDelegate.hpp>
#include <presentations/SlidePreviewListView.hpp>

#include <QPointer>
#include <QStandardItem>
#include <QWidget>

namespace presentations {

SlidePreviewListView::SlidePreviewListView(QWidget* parent) : QListView(parent) {
    QListView::setModel(&m_model);
    setItemDelegate(new SlidePreviewDelegate(this));
    setFrameShape(NoFrame);
    setBackgroundRole(QPalette::Base);
    setAutoFillBackground(true);
    connect(this, &QListView::clicked, [this](const QModelIndex& index) {
        const auto widget{m_model.index(index.row(), index.column()).data(WidgetTypeRole).template value<QPointer<QWidget>>()};
        emit slideSelected(widget);
    });
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
        selectionModel()->select(m_model.index(index, 0), QItemSelectionModel::ClearAndSelect);
        scrollTo(m_model.index(index, 0));
    }
    emit slideSelected(m_model.index(index, 0).data(WidgetTypeRole).value<QPointer<QWidget>>());
}

void SlidePreviewListView::handleCanvasUpdate(const int index) {
    if (index >= 0 && index < m_model.rowCount()) {
        update(m_model.index(index, 0));
    }
}

} // namespace presentations