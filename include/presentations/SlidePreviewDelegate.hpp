#ifndef PRESENTATIONS_SLIDE_PREVIEW_DELEGATE_HPP
#define PRESENTATIONS_SLIDE_PREVIEW_DELEGATE_HPP

#include <QObject>
#include <QStyledItemDelegate>

namespace presentations {

class SlidePreviewDelegate final : public QStyledItemDelegate {
    Q_OBJECT
  public:
    explicit SlidePreviewDelegate(QObject* parent = nullptr);
    void paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const override;
    [[nodiscard]] QSize sizeHint(const QStyleOptionViewItem& option, const QModelIndex& index) const override;
};

} // namespace presentations

#endif // PRESENTATIONS_SLIDE_PREVIEW_DELEGATE_HPP
