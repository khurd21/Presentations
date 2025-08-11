#ifndef PRESENTATIONS_SHORTCUT_MANAGER_HPP
#define PRESENTATIONS_SHORTCUT_MANAGER_HPP

#include <QKeyEvent>
#include <QObject>

namespace presentations {

enum class ShortcutRequest;

/**
 * @class ShortcutManager
 * @brief The ShortcutManager class is used to handle the keyboard shortcuts.
 */
class ShortcutManager final : public QObject {
    Q_OBJECT
  public:
    /**
     * @brief Construct a new ShortcutManager object.
     * @param parent The parent widget.
     */
    explicit ShortcutManager(QObject* parent = nullptr);

    /**
     * @brief The shortcut manager is a singleton. This function returns the instance of the manager.
     * @return The instance of the ShortcutManager.
     */
    static ShortcutManager& instance();

  signals:
    /**
     * @brief Emitted when a shortcut is triggered.
     * @param shortcut The shortcut that was triggered.
     */
    void shortcutTriggered(ShortcutRequest shortcut);

  protected:
    bool eventFilter(QObject* watched, QEvent* event) override;

  private:
    void handleKeyPress(QKeyEvent* event);

    /**
     * @brief
     * Determines if the event matches the specified shortcut key sequence.
     * If so, the `shortcutTriggered` signal is emitted.
     * @param event The key event. Must not be nullptr.
     */
    void handlePreviousSlideShortcut(QKeyEvent* event);

    /**
     * @brief
     * Determines if the event matches the specified shortcut key sequence.
     * If so, the `shortcutTriggered` signal is emitted.
     * @param event The key event. Must not be nullptr.
     */
    void handleNextSlideShortcut(QKeyEvent* event);

    /**
     * @brief
     * Determines if the event matches the specified shortcut key sequence.
     * If so, the `shortcutTriggered` signal is emitted.
     * @param event The key event. Must not be nullptr.
     */
    void handleCreateNewSlidePageShortcut(QKeyEvent* event);

    /**
     * @brief
     * Determines if the event matches the specified shortcut key sequence.
     * If so, the `shortcutTriggered` signal is emitted.
     * @param event The key event. Must not be nullptr.
     */
    void handleDeleteSlideShortcut(QKeyEvent* event);
};

} // namespace presentations

#endif // PRESENTATIONS_SHORTCUT_MANAGER_HPP
