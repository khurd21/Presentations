#ifndef PRESENTATIONS_SLIDE_CODE_MANAGER_HPP
#define PRESENTATIONS_SLIDE_CODE_MANAGER_HPP

#include <presentations/CodeParser.hpp>
#include <presentations/CodeThemeConfig.hpp>

#include <QObject>
#include <QPointer>
#include <QString>

#include <optional>
#include <vector>

namespace presentations {
class CodeEditor;
class CanvasView;
class SlideWidget;

/**
 * @class PresentationManager
 * @brief Manages the creation, organization, and display of presentations.
 *
 * The PresentationManager class provides functionality to create, manage, and
 * display presentation slides. It allows customization and dynamic modifications
 * to existing presentations, enabling better control over presentation workflows.
 */
class PresentationManager final : public QObject {
    Q_OBJECT
  public:
    /**
     * @brief Construct a new PresentationManager.
     * @param parent The parent widget.
     */
    explicit PresentationManager(QObject* parent = nullptr);

    /**
     * @brief Sets the code editor instance used for managing code content in the presentation.
     * @param editor Pointer to the CodeEditor instance to be associated with the PresentationManager.
     */
    void setCodeEditor(CodeEditor* editor);

    /**
     * @brief Sets the canvas view instance used for displaying the presentation.
     * @param view Pointer to the CanvasView instance to be associated with the PresentationManager.
     */
    void setCanvasView(CanvasView* view);

  signals:
    /**
     * @brief Emitted when a new slide is created.
     * @param slideWidget The slide widget that was created.
     */
    void newSlideMade(QWidget* slideWidget);

    /**
     * @brief Emitted when a slide is deleted.
     * @param slideNumber The slide number that was deleted.
     */
    void slideDeleted(int slideNumber);

  public slots:
    /**
     * @brief Handles the change of the current slide.
     * @param index The index of the slide that was changed.
     */
    void onSlideNumberChanged(int index);

    /**
     * @brief Handles the deletion of a slide.
     * @param index The index of the slide to delete.
     */
    void onDeleteSlide(int index);

    /**
     * @brief Handles the creation of a new slide.
     */
    void onMakeNewSlide();

  private slots:
    void onCodeChanged();

  private:
    std::vector<QString> m_codeEditorText;
    std::vector<QPointer<SlideWidget>> m_slideWidgets;
    std::optional<int> m_slideNumber;

    CodeThemeConfig m_themeConfig;
    CodeParser m_codeParser;
    QPointer<CodeEditor> m_primaryCodeEditor;
    QPointer<CanvasView> m_primaryCanvasView;
};

} // namespace presentations

#endif // PRESENTATIONS_SLIDE_CODE_MANAGER_HPP
