#ifndef PRESENTATIONS_SLIDE_PREVIEW_LIST_VIEW_HPP
#define PRESENTATIONS_SLIDE_PREVIEW_LIST_VIEW_HPP

#include <QListView>
#include <QStandardItemModel>
#include <QWidget>

namespace presentations {

class SlidePreviewListView final : public QListView {
    Q_OBJECT
  public:
    explicit SlidePreviewListView(QWidget* parent = nullptr);
    void addSlide(int number, QWidget* previewWidget);
    void handleCanvasUpdate(int index);

    enum {
        SlideNumberRole = Qt::UserRole,
        WidgetTypeRole = Qt::UserRole + 1,
    };

  private:
    void setCurrentSlide(int index);

    QStandardItemModel m_model;
};

} // namespace presentations

#endif // PRESENTATIONS_SLIDE_PREVIEW_LIST_VIEW_HPP
