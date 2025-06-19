#ifndef PRESENTATIONS_CANVAS_VIEW_HPP
#define PRESENTATIONS_CANVAS_VIEW_HPP

#include <QGestureEvent>
#include <QGraphicsView>
#include <QPoint>
#include <QPropertyAnimation>
#include <QTouchEvent>

namespace presentations {

class CanvasView final : public QGraphicsView {
    Q_OBJECT
    Q_PROPERTY(double zoomLevel READ zoomLevel WRITE setZoomLevel)
  public:
    explicit CanvasView(QWidget* parent = nullptr);

    void clearSlideContent();
    void addSlideContent(QWidget* widget);
    void setSlideWidget(QWidget* slideWidget);
    QWidget* slideWidget() const;

    double zoomLevel() const;
    void setZoomLevel(double zoomLevel);

  protected:
    bool event(QEvent* event) override;
    void wheelEvent(QWheelEvent* event) override;
    void mousePressEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;

  private:
    bool gestureEvent(QGestureEvent* event);

    QPoint m_lastPanPosition;
    QPropertyAnimation* m_zoomAnimation{};
    QGraphicsProxyWidget* m_proxy{};
    QGraphicsScene* m_scene{};
    double m_initialZoom{1.0};
    double m_targetScale{1.0};
    bool m_isAnimating{};
};

} // namespace presentations

#endif // PRESENTATIONS_CANVAS_VIEW_HPP
