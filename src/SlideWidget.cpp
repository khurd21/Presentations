#include <presentations/SlideWidget.hpp>

#include <QPainter>

namespace presentations {

SlideWidget::SlideWidget(QWidget* parent) : QWidget(parent) { setMinimumSize(1200, 600); }

void SlideWidget::paintEvent(QPaintEvent* event) {
    QPainter painter(this);
    painter.fillRect(rect(), Qt::white);
}

} // namespace presentations