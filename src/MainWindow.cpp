#include "ui_MainWindow.h"

#include <presentations/MainWindow.hpp>
#include <presentations/SlidePreviewDelegate.hpp>

#include <QModelIndex>

#include <memory>

namespace presentations {

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent), m_ui(std::make_unique<Ui::MainWindow>()) {
    m_ui->setupUi(this);
    m_presentationManager.setCodeEditor(m_ui->codeEditor);
    m_presentationManager.setCanvasView(m_ui->graphicsView);

    connect(m_ui->previewList, &SlidePreviewListView::clicked, this, &MainWindow::onSlideSelection);
    connect(m_ui->graphicsView, &CanvasView::canvasContentChanged, this, [this] { m_ui->previewList->update(); });
    connect(m_ui->addSlideButton, &QPushButton::pressed, &m_presentationManager, &PresentationManager::onMakeNewSlide);
    connect(&m_presentationManager, &PresentationManager::newSlideMade, this, &MainWindow::onNewSlideMade);
}

MainWindow::~MainWindow() = default;

void MainWindow::onNewSlideMade(const int slideNumber, QWidget* slideWidget) const { m_ui->previewList->addSlide(slideNumber, slideWidget); }

void MainWindow::onSlideSelection(const QModelIndex& index) { m_presentationManager.onSlideNumberChanged(index.row() + 1); }

} // namespace presentations