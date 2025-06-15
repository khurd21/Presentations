#ifndef PRESENTATIONS_MAIN_WINDOW_HPP
#define PRESENTATIONS_MAIN_WINDOW_HPP

#include <QMainWindow>
#include <QStandardItemModel>
#include <QWidget>

#include <memory>

namespace Ui {
class MainWindow;
}

namespace presentations {

class CanvasView;

class MainWindow final : public QMainWindow {
    Q_OBJECT
  public:
    explicit MainWindow(QWidget* parent = nullptr);
    ~MainWindow() override;

  private slots:
    void handleSlideSelection(QWidget* widget);

  private:
    std::unique_ptr<Ui::MainWindow> m_ui;
};

} // namespace presentations

#endif // PRESENTATIONS_MAIN_WINDOW_HPP
