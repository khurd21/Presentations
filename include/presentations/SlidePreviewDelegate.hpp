#ifndef PRESENTATIONS_SLIDE_PREVIEW_DELEGATE_HPP
#define PRESENTATIONS_SLIDE_PREVIEW_DELEGATE_HPP

#include <QObject>
#include <QStyledItemDelegate>

namespace presentations {

/**
 * @class SlidePreviewDelegate
 * @brief The SlidePreviewDelegate class is used to render the slide preview.
 */
class SlidePreviewDelegate final : public QStyledItemDelegate {
    Q_OBJECT
  public:
    /**
     * @brief Construct a new SlidePreviewDelegate object.
     * @param parent The parent widget.
     */
    explicit SlidePreviewDelegate(QObject* parent = nullptr);

  protected:
    void paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const override;
    [[nodiscard]] QSize sizeHint(const QStyleOptionViewItem& option, const QModelIndex& index) const override;
};

} // namespace presentations

#endif // PRESENTATIONS_SLIDE_PREVIEW_DELEGATE_HPP
