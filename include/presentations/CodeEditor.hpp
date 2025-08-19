#ifndef PRESENTATIONS_CODE_EDITOR_HPP
#define PRESENTATIONS_CODE_EDITOR_HPP

#include <QLabel>
#include <QPlainTextEdit>
#include <QString>

namespace presentations {

/**
 * @class CodeEditor
 * @brief The CodeEditor class is a simple text editor for code. The content of the
 * code editor is used to render the slide content.
 */
class CodeEditor final : public QWidget {
    Q_OBJECT
  public:
    /**
     * @brief Represents the modes the code editor can be in. Mimics vim behavior.
     */
    enum class Mode {
        Normal,
        Insert,
        Visual,
    };

    /**
     * @brief Construct a new CodeEditor object.
     * @param parent The parent widget.
     */
    explicit CodeEditor(QWidget* parent = nullptr);

    void setMode(Mode mode);

    [[nodiscard]] QString toPlainText() const;
    void setPlainText(const QString& text);

    void clear();

  signals:
    void textChanged();

  protected:
    bool eventFilter(QObject* watched, QEvent* event) override;

  private:
    void updateStatusBar() const;

    Mode m_mode{Mode::Normal};
    int m_slideNumber{};

    QPlainTextEdit* m_editor{};
    QLabel* m_statusBarLabel{};
};

} // namespace presentations

#endif // PRESENTATIONS_CODE_EDITOR_HPP
