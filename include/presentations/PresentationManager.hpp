#ifndef PRESENTATIONS_SLIDE_CODE_MANAGER_HPP
#define PRESENTATIONS_SLIDE_CODE_MANAGER_HPP

#include <presentations/CodeParser.hpp>
#include <presentations/CodeThemeConfig.hpp>

#include <QObject>
#include <QPointer>
#include <QString>

#include <optional>
#include <unordered_map>

namespace presentations {
class CodeEditor;
class CanvasView;
class SlideWidget;

class PresentationManager final : public QObject {
    Q_OBJECT
  public:
    explicit PresentationManager(QObject* parent = nullptr);
    void setCodeEditor(CodeEditor* editor);
    void setCanvasView(CanvasView* view);

  signals:
    void newSlideMade(int slideNumber, QWidget* slideWidget);

  public slots:
    void onSlideNumberChanged(int slideNumber);
    void onMakeNewSlide();

  private slots:
    void onCodeChanged();

  private:
    std::unordered_map<int, QString> m_codeEditorText;
    std::unordered_map<int, QPointer<SlideWidget>> m_slideWidgets;
    std::optional<int> m_slideNumber;

    CodeThemeConfig m_themeConfig;
    CodeParser m_codeParser;
    QPointer<CodeEditor> m_primaryCodeEditor;
    QPointer<CanvasView> m_primaryCanvasView;
};

} // namespace presentations

#endif // PRESENTATIONS_SLIDE_CODE_MANAGER_HPP
