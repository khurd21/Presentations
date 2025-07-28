#include <presentations/CanvasView.hpp>

#include <QGraphicsProxyWidget>
#include <QGraphicsView>
#include <QLayout>
#include <QLayoutItem>
#include <QPainter>
#include <QTimer>
#include <QWheelEvent>

#include <cmath>

namespace presentations {

CanvasView::CanvasView(QWidget* parent) : QGraphicsView(parent) {
    m_zoomAnimation = new QPropertyAnimation(this, "zoomLevel");
    QEasingCurve curve(QEasingCurve::OutBack);
    curve.setAmplitude(1.5);
    curve.setOvershoot(1.2);
    m_zoomAnimation->setEasingCurve(curve);
    m_zoomAnimation->setDuration(450);

    setMouseTracking(true);
    setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
    setDragMode(NoDrag);
    setTransformationAnchor(AnchorUnderMouse);
    setAttribute(Qt::WA_AcceptTouchEvents);
    viewport()->setAttribute(Qt::WA_AcceptTouchEvents);
    grabGesture(Qt::GestureType::PinchGesture);

    connect(m_zoomAnimation, &QPropertyAnimation::finished, [this] { m_isAnimating = false; });
}
void CanvasView::clearSlideContent() {
    if (m_proxy) {
        if (const auto widget = m_proxy->widget()) {
            if (const auto layout = widget->layout()) {
                const QLayoutItem* item{};
                while ((item = layout->takeAt(0))) {
                    delete item->widget();
                    delete item;
                }
                emit canvasContentChanged();
            }
        }
    }
}

void CanvasView::addSlideContent(QWidget* widget) {
    if (m_proxy) {
        if (const auto slide = m_proxy->widget()) {
            if (const auto layout = slide->layout()) {
                layout->addWidget(widget);
                emit canvasContentChanged();
            }
        }
    }
}

void CanvasView::setSlideWidget(QWidget* slideWidget) {
    if (!m_scene) {
        m_scene = new QGraphicsScene(this);
        setScene(m_scene);
    }

    if (m_proxy && m_proxy->widget() == slideWidget) {
        return;
    }
    if (m_proxy) {
        m_proxy->setWidget(nullptr);
        m_scene->removeItem(m_proxy);
        m_proxy->deleteLater();
        m_proxy = nullptr;
    }

    m_proxy = m_scene->addWidget(slideWidget);
    const auto bounds{m_proxy->boundingRect()};
    m_proxy->setPos(-bounds.width() / 2, -bounds.height() / 2);
    m_proxy->setTransformOriginPoint(bounds.center());
    m_proxy->setCacheMode(QGraphicsItem::DeviceCoordinateCache);
    centerOn(m_proxy);
}

double CanvasView::zoomLevel() const { return m_proxy ? m_proxy->scale() : 1.0; }

// ReSharper disable once CppMemberFunctionMayBeConst
void CanvasView::setZoomLevel(double zoomLevel) {
    if (!m_proxy) {
        return;
    }
    m_proxy->setScale(std::clamp(zoomLevel, 0.1, 10.0));
}

bool CanvasView::event(QEvent* event) {
    switch (event->type()) {
    case QEvent::Gesture:
        return gestureEvent(static_cast<QGestureEvent*>(event));
    default:
        return QGraphicsView::event(event);
    }
}

void CanvasView::wheelEvent(QWheelEvent* event) {
    if (event->device()->type() == QInputDevice::DeviceType::TouchPad) {
        return;
    }

    constexpr auto zoomFactor{1.15};
    if (event->angleDelta().y() > 0) {
        m_targetScale = zoomLevel() * zoomFactor;
    } else {
        m_targetScale = zoomLevel() / zoomFactor;
    }
    setZoomLevel(m_targetScale);
    event->accept();
}

void CanvasView::mousePressEvent(QMouseEvent* event) {
    if (event->button() == Qt::LeftButton) {
        m_lastPanPosition = event->pos();
        setCursor(Qt::ClosedHandCursor);
        event->accept();
    } else {
        QWidget::mousePressEvent(event);
    }
}

void CanvasView::mouseMoveEvent(QMouseEvent* event) {
    if (m_proxy && (event->buttons() & Qt::LeftButton)) {
        const auto delta{event->pos() - m_lastPanPosition};
        m_proxy->setPos(m_proxy->pos() + delta);
        m_lastPanPosition = event->pos();
        event->accept();
    } else {
        QWidget::mouseMoveEvent(event);
    }
}

void CanvasView::mouseReleaseEvent(QMouseEvent* event) {
    if (event->button() == Qt::LeftButton) {
        setCursor(Qt::ArrowCursor);
        event->accept();
    } else {
        QWidget::mouseReleaseEvent(event);
    }
}

bool CanvasView::gestureEvent(QGestureEvent* event) {
    if (QGesture* pinch = event->gesture(Qt::PinchGesture)) {
        const auto pinchGesture{static_cast<QPinchGesture*>(pinch)};
        if (const auto& state{pinchGesture->state()}; Qt::GestureStarted == state) {
            m_initialZoom = zoomLevel();
            m_zoomAnimation->stop();
        } else if (Qt::GestureUpdated == state) {
            const auto scaleFactor{pinchGesture->totalScaleFactor()};
            m_targetScale = m_initialZoom * scaleFactor;
            setZoomLevel(m_targetScale);
        } else if (Qt::GestureFinished == state) {
            m_targetScale = std::round(zoomLevel() * 10) / 10.0;
            const auto overshoot{m_targetScale * 1.05};
            m_zoomAnimation->setStartValue(zoomLevel());
            m_zoomAnimation->setEndValue(overshoot);
            m_zoomAnimation->start();
        }
        return true;
    }
    return false;
}

} // namespace presentations