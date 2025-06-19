#include <presentations/CanvasView.hpp>
#include <presentations/CodeEditor.hpp>
#include <presentations/ElementRenderer.hpp>
#include <presentations/ParsedElement.hpp>
#include <presentations/PresentationManager.hpp>

#include <QFile>
#include <QString>
#include <QVBoxLayout>

namespace presentations {

PresentationManager::PresentationManager(QObject* parent) : QObject(parent), m_codeParser(m_themeConfig) {
    m_themeConfig.loadFromFile(QFile(":/defaults/codeEditorDefaults.json"));
}

void PresentationManager::setCodeEditor(CodeEditor* editor) {
    m_codeEditor = editor;
    connect(m_codeEditor, &CodeEditor::textChanged, this, &PresentationManager::onCodeChanged);
}

void PresentationManager::setCanvasView(CanvasView* view) { m_canvasView = view; }

void PresentationManager::onCodeChanged() {
    if (!m_codeEditor || !m_canvasView) {
        return;
    }
    const auto layout{new QVBoxLayout};
    layout->setContentsMargins(0, 0, 0, 0);
    layout->addStretch(1);

    const auto contentLayout{new QVBoxLayout};
    contentLayout->setSpacing(12);
    contentLayout->setSizeConstraint(QLayout::SetMinAndMaxSize);
    for (const auto& element : m_codeParser.parse(m_codeEditor->toPlainText())) {
        contentLayout->addWidget(ElementRenderer::render(element, m_canvasView));
    }
    const auto contentWidget{new QWidget};
    contentWidget->setLayout(contentLayout);
    contentWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    layout->addWidget(contentWidget, 0);
    layout->addStretch(1);

    const auto container{new QWidget};
    container->setLayout(layout);
    m_canvasView->clearSlideContent();
    m_canvasView->addSlideContent(container);
}

} // namespace presentations