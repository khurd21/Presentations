#ifndef PRESENTATIONS_SHORTCUT_MANAGER_HPP
#define PRESENTATIONS_SHORTCUT_MANAGER_HPP

#include <QKeyEvent>
#include <QObject>

namespace presentations {

enum class ShortcutRequest;

// TODO: Add docs
// TODO: Make sure all of the shortcut signals are working.
// TODO: Make sure all of the slots are working.
class ShortcutManager final : public QObject {
    Q_OBJECT
  public:
    explicit ShortcutManager(QObject* parent = nullptr);
    static ShortcutManager& instance();

  signals:
    void shortcutTriggered(ShortcutRequest shortcut);

  protected:
    bool eventFilter(QObject* watched, QEvent* event) override;

  private:
    void handleKeyPress(QKeyEvent* event);

    void handlePreviousSlideShortcut(QKeyEvent* event);
    void handleNextSlideShortcut(QKeyEvent* event);
    void handleCreateNewSlidePageShortcut(QKeyEvent* event);
    void handleDeleteSlideShortcut(QKeyEvent* event);
};

} // namespace presentations

#endif // PRESENTATIONS_SHORTCUT_MANAGER_HPP
