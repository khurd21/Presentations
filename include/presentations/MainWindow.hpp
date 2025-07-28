#ifndef PRESENTATIONS_MAIN_WINDOW_HPP
#define PRESENTATIONS_MAIN_WINDOW_HPP

#include <presentations/PresentationManager.hpp>

#include <QMainWindow>
#include <QWidget>

#include <memory>

namespace Ui {
class MainWindow;
}

namespace presentations {

class CanvasView;

/**
 * @class MainWindow
 * @brief The main window of the application.
 */
class MainWindow final : public QMainWindow {
    Q_OBJECT
  public:
    /**
     * @brief Construct a new MainWindow object.
     * @param parent The parent widget.
     */
    explicit MainWindow(QWidget* parent = nullptr);
    ~MainWindow() override;

  private slots:
    /**
     * @brief Handles the selection of a slide.
     * @param index The index of the selected slide.
     */
    void onSlideSelection(const QModelIndex& index);

    /**
     * @brief Handles the creation of a new slide.
     * @param slideWidget The slide widget that was created.
     */
    void onNewSlideMade(QWidget* slideWidget) const;

    /**
     * @brief Handles the deletion of a slide.
     * @param slideNumber The slide number that was deleted.
     */
    void onSlideDeleted(int slideNumber) const;

  private:
    std::unique_ptr<Ui::MainWindow> m_ui;
    PresentationManager m_presentationManager;
};

} // namespace presentations

#endif // PRESENTATIONS_MAIN_WINDOW_HPP
