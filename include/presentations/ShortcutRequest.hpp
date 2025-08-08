#ifndef PRESENTATIONS_SHORTCUT_REQUEST_HPP
#define PRESENTATIONS_SHORTCUT_REQUEST_HPP

namespace presentations {

/**
 * @enum ShortcutRequest
 * @brief
 * The ShortcutRequest enum is used to identify the shortcut request.
 * All shortcuts we want to add support for should be added here.
 */
enum class ShortcutRequest {
    PreviousSlide,
    NextSlide,
    CreateNewSlidePage,
    DeleteCurrentSlidePage,
};

} // namespace presentations

#endif // PRESENTATIONS_SHORTCUT_REQUEST_HPP
