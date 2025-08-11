#include <presentations/ShortcutManager.hpp>
#include <presentations/ShortcutRequest.hpp>

#include <QEvent>
#include <QKeyEvent>
#include <QKeySequence>
#include <QObject>
#include <QShortcut>

namespace presentations {

ShortcutManager::ShortcutManager(QObject* parent) : QObject(parent) { qApp->installEventFilter(this); }

ShortcutManager& ShortcutManager::instance() {
    static ShortcutManager instance;
    return instance;
}

bool ShortcutManager::eventFilter(QObject* watched, QEvent* event) {
    if (event->type() == QEvent::KeyPress) {
        return handleKeyPress(dynamic_cast<QKeyEvent*>(event));
    }
    return QObject::eventFilter(watched, event);
}

bool ShortcutManager::handleKeyPress(QKeyEvent* event) {
    bool isHandled{};
    isHandled |= handlePreviousSlideShortcut(event);
    isHandled |= handleNextSlideShortcut(event);
    isHandled |= handleCreateNewSlidePageShortcut(event);
    isHandled |= handleDeleteSlideShortcut(event);
    return isHandled;
}

bool ShortcutManager::handlePreviousSlideShortcut(QKeyEvent* event) {
    if (event->modifiers() == Qt::ControlModifier && event->key() == Qt::Key_K) {
        emit shortcutTriggered(ShortcutRequest::PreviousSlide);
        event->accept();
        return true;
    }
    return false;
}

bool ShortcutManager::handleNextSlideShortcut(QKeyEvent* event) {
    if (event->modifiers() == Qt::ControlModifier && event->key() == Qt::Key_J) {
        emit shortcutTriggered(ShortcutRequest::NextSlide);
        event->accept();
        return true;
    }
    return false;
}

bool ShortcutManager::handleCreateNewSlidePageShortcut(QKeyEvent* event) {
    const auto pressedKey{static_cast<QKeySequence>(static_cast<int>(event->key() | event->modifiers()))};
    if (pressedKey.matches(QKeySequence::New) || (event->modifiers() == Qt::ControlModifier && event->key() == Qt::Key_N)) {
        emit shortcutTriggered(ShortcutRequest::CreateNewSlidePage);
        event->accept();
        return true;
    }
    return false;
}

bool ShortcutManager::handleDeleteSlideShortcut(QKeyEvent* event) {
    const auto pressedKey{static_cast<QKeySequence>(static_cast<int>(event->key() | event->modifiers()))};
    if (pressedKey.matches(QKeySequence::Delete) ||
        (event->modifiers() == Qt::ControlModifier && (event->key() == Qt::Key_Delete || event->key() == Qt::Key_D))) {
        emit shortcutTriggered(ShortcutRequest::DeleteCurrentSlidePage);
        event->accept();
        return true;
    }
    return false;
}

} // namespace presentations