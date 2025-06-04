#include "ui_MainWindow.h"

#include <presentations/MainWindow.hpp>
#include <presentations/SlideWidget.hpp>

#include <memory>

namespace presentations {

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent), m_ui(std::make_unique<Ui::MainWindow>()) {
    m_ui->setupUi(this);
    // If parented, it will not be able to embed the widget.
    m_ui->graphicsView->setSlideWidget(new SlideWidget());
}

MainWindow::~MainWindow() = default;

} // namespace presentations