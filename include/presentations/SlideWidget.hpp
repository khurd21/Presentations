//
// Created by Kyle Hurd on 6/3/25.
//

#ifndef PRESENTATIONS_SLIDE_WIDGET_HPP
#define PRESENTATIONS_SLIDE_WIDGET_HPP
#include <QWidget>

namespace presentations {

/**
 * @class SlideWidget
 * @brief The SlideWidget class is a simple widget that is used to render the slide content.
 */
class SlideWidget final : public QWidget {
    Q_OBJECT
  public:
    /**
     * @brief Construct a new SlideWidget object.
     * @param parent The parent widget.
     */
    explicit SlideWidget(QWidget* parent = nullptr);

  protected:
    void paintEvent(QPaintEvent* event) override;
};

} // namespace presentations

#endif // PRESENTATIONS_SLIDE_WIDGET_HPP
