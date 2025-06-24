#include <presentations/CanvasView.hpp>
#include <presentations/SlidePreviewDelegate.hpp>
#include <presentations/SlidePreviewListView.hpp>

#include <QColor>
#include <QModelIndex>
#include <QPainter>
#include <QPainterPath>
#include <QPointer>
#include <QSize>
#include <QString>
#include <QStyleOptionViewItem>

namespace presentations {

SlidePreviewDelegate::SlidePreviewDelegate(QObject* parent) : QStyledItemDelegate(parent) {}

void SlidePreviewDelegate::paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const {
    painter->save();

    const auto isSelected{option.state & QStyle::State_Selected};
    const auto isHovered{option.state & QStyle::State_MouseOver};
    const auto backgroundRect{option.rect.adjusted(2, 2, -2, -2)};
    const auto& palette{option.palette};
    auto fillColor{palette.base().color()};
    auto textColor{palette.text().color()};
    if (isSelected) {
        fillColor = palette.highlight().color();
    } else if (isHovered) {
        fillColor = palette.alternateBase().color();
    }
    painter->setRenderHint(QPainter::Antialiasing);

    QPainterPath path;
    path.addRoundedRect(backgroundRect, 16, 16);
    painter->setClipPath(path);

    painter->fillPath(path, fillColor);
    const auto slideNumber{index.data(SlidePreviewListView::SlideNumberRole).toString()};
    auto font{option.font};
    font.setBold(true);
    painter->setFont(font);
    painter->setPen(textColor);
    constexpr auto verticalMargin{6};
    constexpr auto marginLeft{6};

    QFontMetrics metrics(font);
    const auto charWidth{metrics.horizontalAdvance("999")};
    auto textRect{backgroundRect};
    textRect.setTop(backgroundRect.top() + verticalMargin);
    textRect.setBottom(backgroundRect.bottom() - verticalMargin);
    textRect.setLeft(backgroundRect.left() + marginLeft);
    textRect.setRight(textRect.left() + charWidth);
    painter->drawText(textRect, Qt::AlignLeft | Qt::AlignBottom, slideNumber);

    if (const auto canvas{index.data(SlidePreviewListView::WidgetTypeRole).value<QPointer<QWidget>>()}) {
        constexpr auto spacing{6};
        constexpr auto imageMargin{4};
        constexpr auto cornerRadius{16};

        const auto top{backgroundRect.top() + verticalMargin + imageMargin};
        const auto bottom{backgroundRect.bottom() - verticalMargin - imageMargin};
        const auto height{bottom - top};
        const auto numberWidth{metrics.horizontalAdvance("999")};
        const auto left{backgroundRect.left() + marginLeft + numberWidth + spacing + imageMargin};
        const auto right{backgroundRect.right() - spacing - imageMargin};
        const auto width{right - left};
        const QRect imageRect{left, top, width, height};

        if (const auto preview{canvas->grab()}; !preview.isNull()) {
            const auto previewSize{preview.size()};
            const auto previewAspect{static_cast<double>(previewSize.width()) / previewSize.height()};
            const auto rectAspect{static_cast<double>(imageRect.width()) / imageRect.height()};
            QSize fittedSize;
            if (previewAspect > rectAspect) {
                fittedSize = {imageRect.width(), static_cast<int>(imageRect.width() / previewAspect)};
            } else {
                fittedSize = {static_cast<int>(imageRect.height() * previewAspect), imageRect.height()};
            }
            const auto x{imageRect.left() + (imageRect.width() - fittedSize.width()) / 2};
            const auto y{imageRect.top() + (imageRect.height() - fittedSize.height()) / 2};
            const QRect aspectFitRect{x, y, fittedSize.width(), fittedSize.height()};
            const auto scaledPreview{preview.scaled(fittedSize * 2, Qt::KeepAspectRatio, Qt::SmoothTransformation)};
            painter->drawPixmap(aspectFitRect.topLeft(), scaledPreview);
        }
    }

    painter->restore();
}

QSize SlidePreviewDelegate::sizeHint(const QStyleOptionViewItem&, const QModelIndex&) const { return QSize(100, 110); }

} // namespace presentations