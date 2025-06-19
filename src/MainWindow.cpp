#include "ui_MainWindow.h"

#include <presentations/MainWindow.hpp>
#include <presentations/SlidePreviewDelegate.hpp>
#include <presentations/SlideWidget.hpp>

#include <memory>

namespace presentations {

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent), m_ui(std::make_unique<Ui::MainWindow>()) {
    m_ui->setupUi(this);
    m_presentationManager.setCodeEditor(m_ui->codeEditor);
    m_presentationManager.setCanvasView(m_ui->graphicsView);

    // TODO: This is just to be able to preview the slides.
    // TODO: Remove once there is support for adding slides in the UI.
    const auto firstSlide{new SlideWidget()};
    m_ui->previewList->addSlide(1, firstSlide);
    m_ui->previewList->addSlide(2, new SlideWidget());
    m_ui->previewList->addSlide(3, new SlideWidget());
    m_ui->previewList->addSlide(4, new SlideWidget());
    m_ui->previewList->addSlide(5, new SlideWidget());
    m_ui->previewList->addSlide(6, new SlideWidget());
    m_ui->previewList->addSlide(7, new SlideWidget());
    m_ui->previewList->addSlide(8, new SlideWidget());
    m_ui->previewList->addSlide(9, new SlideWidget());
    m_ui->previewList->addSlide(10, new SlideWidget());
    m_ui->previewList->addSlide(11, new SlideWidget());
    m_ui->previewList->addSlide(12, new SlideWidget());
    m_ui->previewList->addSlide(13, new SlideWidget());
    handleSlideSelection(firstSlide);
    m_ui->previewList->setCurrentIndex(m_ui->previewList->model()->index(0, 0));
    m_ui->previewList->scrollTo(m_ui->previewList->currentIndex());
    connect(m_ui->previewList, &SlidePreviewListView::slideSelected, this, &MainWindow::handleSlideSelection);
}

MainWindow::~MainWindow() = default;

// ReSharper disable once CppMemberFunctionMayBeConst
void MainWindow::handleSlideSelection(QWidget* widget) {
    if (const auto slideWidget{dynamic_cast<SlideWidget*>(widget)}) {
        m_ui->graphicsView->setSlideWidget(slideWidget);
    }
}

} // namespace presentations