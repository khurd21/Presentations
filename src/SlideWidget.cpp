#include <presentations/SlideWidget.hpp>

#include <QPainter>
#include <QVBoxLayout>

namespace presentations {

SlideWidget::SlideWidget(QWidget* parent) : QWidget(parent) {
    setMinimumSize(1200, 600);
    setLayout(new QVBoxLayout(this));
}

void SlideWidget::paintEvent(QPaintEvent* event) {
    QPainter painter(this);
    painter.fillRect(rect(), Qt::white);
}

} // namespace presentations