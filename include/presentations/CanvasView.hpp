#ifndef PRESENTATIONS_CANVAS_VIEW_HPP
#define PRESENTATIONS_CANVAS_VIEW_HPP

#include <QGestureEvent>
#include <QGraphicsView>
#include <QPoint>
#include <QPropertyAnimation>
#include <QTouchEvent>

namespace presentations {

/**
 * @class CanvasView
 * @brief
 * The CanvasView class is the main view of the presentation.
 * It displays the slide content for the current slide and handles zooming, panning,
 * and touch events to change the position of the view.
 */
class CanvasView final : public QGraphicsView {
    Q_OBJECT
    Q_PROPERTY(double zoomLevel READ zoomLevel WRITE setZoomLevel)
  public:
    /**
     * @brief Construct a new CanvasView object.
     * @param parent The parent widget.
     */
    explicit CanvasView(QWidget* parent = nullptr);

    /**
     * @brief
     * Clears the slide content. The slide content is the widget that is displayed
     * inside the canvas.
     */
    void clearSlideContent();

    /**
     * @brief Adds the specified widget to the slide content.
     * @param widget The widget to be added.
     */
    void addSlideContent(QWidget* widget);

    /**
     * @brief Sets the slide widget. This is the
     * @param slideWidget
     */
    void setSlideWidget(QWidget* slideWidget);

    /**
     * @brief Gets the zoom level.
     * @return The zoom level.
     */
    [[nodiscard]] double zoomLevel() const;

    /**
     * @brief Sets the zoom level.
     * @param zoomLevel The zoom level.
     */
    void setZoomLevel(double zoomLevel);

  signals:
    /**
     * @brief Emitted when the slide content has changed.
     */
    void canvasContentChanged();

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
