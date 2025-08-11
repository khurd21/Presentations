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
    connect(m_ui->graphicsView, &CanvasView::canvasContentChanged, this, [this] { m_ui->previewList->viewport()->update(); });
    connect(&m_presentationManager, &PresentationManager::newSlideMade, this, &MainWindow::onNewSlideMade);
    connect(&m_presentationManager, &PresentationManager::slideDeleted, this, &MainWindow::onSlideDeleted);

    connect(m_ui->previewList, &SlidePreviewListView::slideCreateRequested, &m_presentationManager, &PresentationManager::onMakeNewSlide);
    connect(m_ui->previewList, &SlidePreviewListView::slideDeleteRequested, &m_presentationManager, &PresentationManager::onDeleteSlide);
}

MainWindow::~MainWindow() = default;

void MainWindow::onNewSlideMade(QWidget* slideWidget) const { m_ui->previewList->addSlide(slideWidget); }

void MainWindow::onSlideDeleted(const int slideNumber) const { m_ui->previewList->removeSlide(slideNumber); }

void MainWindow::onSlideSelection(const QModelIndex& index) { m_presentationManager.onSlideNumberChanged(index.row()); }

} // namespace presentations