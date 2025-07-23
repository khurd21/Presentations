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

    /**
     * Adds a slide to the list.
     * @param previewWidget The widget to be displayed in the preview.
     */
    void addSlide(QWidget* previewWidget);

    /**
     * Removes a slide from the list.
     * @param index The slide number. Value is 0-based.
     */
    void removeSlide(int index);

    /**
     * Handles an update to the canvas at the specified index.
     * Updates the displayed representation of the slide preview for the given index.
     * @param index The index of the slide preview to update. Value is 0-based.
     */
    void handleCanvasUpdate(int index);

    enum {
        SlideNumberRole = Qt::UserRole,
        WidgetTypeRole = Qt::UserRole + 1,
        SlideIndexRole = Qt::UserRole + 2,
    };

  signals:
    /**
     * Emitted when a slide is requested to be deleted.
     * @param slideNumber The slide number. Value is 1-based.
     */
    void slideDeleteRequested(int slideNumber);

    /**
     * Emitted when a new slide is requested to be created.
     */
    void slideCreateRequested();

  protected:
    void keyPressEvent(QKeyEvent* event) override;

  private:
    /**
     * Sets the current slide to the specified index.
     * @param index The index of the slide to set as current. Value is 0-based.
     */
    void setCurrentSlide(int index);

    QStandardItemModel m_model;
};

} // namespace presentations

#endif // PRESENTATIONS_SLIDE_PREVIEW_LIST_VIEW_HPP
