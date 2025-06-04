#ifndef PRESENTATIONS_MAIN_WINDOW_HPP
#define PRESENTATIONS_MAIN_WINDOW_HPP

#include <QMainWindow>

#include <memory>

namespace Ui {
class MainWindow;
}

namespace presentations {

class MainWindow final : public QMainWindow {
    Q_OBJECT
  public:
    explicit MainWindow(QWidget* parent = nullptr);
    ~MainWindow() override;

  private:
    std::unique_ptr<Ui::MainWindow> m_ui;
};

} // namespace presentations

#endif // PRESENTATIONS_MAIN_WINDOW_HPP
