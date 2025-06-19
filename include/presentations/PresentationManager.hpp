#ifndef PRESENTATIONS_SLIDE_CODE_MANAGER_HPP
#define PRESENTATIONS_SLIDE_CODE_MANAGER_HPP

#include <presentations/CodeParser.hpp>
#include <presentations/CodeThemeConfig.hpp>

#include <QObject>
#include <QPointer>
#include <QString>

namespace presentations {
class CodeEditor;
class CanvasView;

class PresentationManager final : public QObject {
    Q_OBJECT
  public:
    explicit PresentationManager(QObject* parent = nullptr);
    void setCodeEditor(CodeEditor* editor);
    void setCanvasView(CanvasView* view);

  private slots:
    void onCodeChanged();

  private:
    CodeThemeConfig m_themeConfig;
    CodeParser m_codeParser;
    QPointer<CodeEditor> m_codeEditor{};
    QPointer<CanvasView> m_canvasView{};
};

} // namespace presentations

#endif // PRESENTATIONS_SLIDE_CODE_MANAGER_HPP
