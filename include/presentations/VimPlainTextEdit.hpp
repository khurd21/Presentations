#ifndef PRESENTATIONS_VIM_PLAIN_TEXT_EDIT_HPP
#define PRESENTATIONS_VIM_PLAIN_TEXT_EDIT_HPP

#include <QPlainTextEdit>

namespace presentations {

class VimPlainTextEdit final : public QPlainTextEdit {
    Q_OBJECT
  public:
    explicit VimPlainTextEdit(QWidget* parent = nullptr);
    void setBlockCursor(bool enabled);

  protected:
    void paintEvent(QPaintEvent* event) override;

  private:
    bool m_blockCursor{};
};

} // namespace presentations

#endif // PRESENTATIONS_VIM_PLAIN_TEXT_EDIT_HPP
