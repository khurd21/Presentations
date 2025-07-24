#include <presentations/CanvasView.hpp>
#include <presentations/CodeEditor.hpp>
#include <presentations/ElementRenderer.hpp>
#include <presentations/ParsedElement.hpp>
#include <presentations/PresentationManager.hpp>
#include <presentations/SlideWidget.hpp>

#include <QFile>
#include <QSignalBlocker>
#include <QString>
#include <QVBoxLayout>

namespace presentations {

PresentationManager::PresentationManager(QObject* parent) : QObject(parent), m_codeParser(m_themeConfig) {
    m_themeConfig.loadFromFile(QFile(":/defaults/codeEditorDefaults.json"));
}

void PresentationManager::setCodeEditor(CodeEditor* editor) {
    m_primaryCodeEditor = editor;
    connect(m_primaryCodeEditor.get(), &CodeEditor::textChanged, this, &PresentationManager::onCodeChanged);
}

void PresentationManager::setCanvasView(CanvasView* view) { m_primaryCanvasView = view; }

void PresentationManager::onSlideNumberChanged(const int index) {
    if (index < 0 || index >= m_slideWidgets.size() || index >= m_codeEditorText.size()) {
        qWarning() << "Slide index number out of range";
        return;
    }
    m_slideNumber = index;
    m_primaryCanvasView->setSlideWidget(m_slideWidgets.at(index));

    QSignalBlocker blocker{m_primaryCodeEditor};
    m_primaryCodeEditor->setPlainText(m_codeEditorText.at(index));
}

void PresentationManager::onMakeNewSlide() {
    if (!m_slideNumber.has_value()) {
        m_slideNumber = -1;
    }
    m_slideNumber.value() += 1;
    m_slideWidgets.emplace_back(new SlideWidget());
    m_codeEditorText.emplace_back("");
    emit newSlideMade(m_slideWidgets.back());
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

void PresentationManager::onDeleteSlide(const int index) {
    if (index < 0 || index >= m_slideWidgets.size()) {
        qWarning() << "Slide index number out of range";
        return;
    }

    if (m_slideNumber.has_value()) {
        if (m_slideNumber.value() == index) {
            if (m_slideWidgets.size() == 1) {
                m_primaryCanvasView->setSlideWidget(nullptr);
                if (m_primaryCodeEditor) {
                    QSignalBlocker blocker{m_primaryCodeEditor};
                    m_primaryCodeEditor->clear();
                }
            }
            m_slideNumber = std::nullopt;
        }
    } else if (m_slideNumber.value() > index) {
        m_slideNumber.value() -= 1;
    }

    if (m_slideWidgets.at(index)) {
        m_slideWidgets.at(index)->deleteLater();
    }

    if (m_slideNumber.has_value() && !m_slideWidgets.empty() && m_primaryCanvasView) {
        m_primaryCanvasView->setSlideWidget(m_slideWidgets[m_slideNumber.value()]);
    }

    m_slideWidgets.erase(m_slideWidgets.begin() + index);
    m_codeEditorText.erase(m_codeEditorText.begin() + index);
    emit slideDeleted(index);
}

} // namespace presentations
