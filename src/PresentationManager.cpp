#include <presentations/CanvasView.hpp>
#include <presentations/CodeEditor.hpp>
#include <presentations/ElementRenderer.hpp>
#include <presentations/ParsedElement.hpp>
#include <presentations/PresentationManager.hpp>
#include <presentations/SlideWidget.hpp>

#include <QFile>
#include <QString>
#include <QVBoxLayout>

namespace presentations {

PresentationManager::PresentationManager(QObject* parent) : QObject(parent), m_codeParser(m_themeConfig) {
    m_themeConfig.loadFromFile(QFile(":/defaults/codeEditorDefaults.json"));
}

void PresentationManager::setCodeEditor(CodeEditor* editor) {
    m_primaryCodeEditor = editor;
    connect(m_primaryCodeEditor, &CodeEditor::textChanged, this, &PresentationManager::onCodeChanged);
}

void PresentationManager::setCanvasView(CanvasView* view) { m_primaryCanvasView = view; }

void PresentationManager::onSlideNumberChanged(const int slideNumber) {
    if (slideNumber < 1 || slideNumber > m_slideWidgets.size() || slideNumber > m_codeEditorText.size()) {
        qWarning() << "Slide number out of range";
        return;
    }
    m_slideNumber = slideNumber;
    m_primaryCanvasView->setSlideWidget(m_slideWidgets.at(slideNumber));
    m_primaryCodeEditor->setPlainText(m_codeEditorText.at(slideNumber));
}

void PresentationManager::onMakeNewSlide() {
    if (!m_slideNumber.has_value()) {
        m_slideNumber = 0;
    }
    m_slideNumber.value() += 1;
    const auto slideWidget{new SlideWidget()};
    m_slideWidgets.insert({m_slideNumber.value(), slideWidget});
    m_codeEditorText.insert({m_slideNumber.value(), ""});
    emit newSlideMade(m_slideNumber.value(), slideWidget);
}

void PresentationManager::onCodeChanged() {
    if (!m_primaryCodeEditor || !m_primaryCanvasView || !m_slideNumber.has_value()) {
        return;
    }

    m_codeEditorText.at(m_slideNumber.value()) = m_primaryCodeEditor->toPlainText();

    const auto layout{new QVBoxLayout};
    layout->setContentsMargins(0, 0, 0, 0);
    layout->addStretch(1);

    const auto contentLayout{new QVBoxLayout};
    contentLayout->setSpacing(12);
    contentLayout->setSizeConstraint(QLayout::SetMinAndMaxSize);
    for (const auto& element : m_codeParser.parse(m_primaryCodeEditor->toPlainText())) {
        contentLayout->addWidget(ElementRenderer::render(element, m_primaryCanvasView));
    }
    const auto contentWidget{new QWidget};
    contentWidget->setLayout(contentLayout);
    contentWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    layout->addWidget(contentWidget, 0);
    layout->addStretch(1);

    const auto container{new QWidget};
    container->setLayout(layout);
    m_primaryCanvasView->clearSlideContent();
    m_primaryCanvasView->addSlideContent(container);
}

} // namespace presentations