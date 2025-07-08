#ifndef PRESENTATIONS_CODE_PARSER_HPP
#define PRESENTATIONS_CODE_PARSER_HPP

#include <presentations/CodeThemeConfig.hpp>

#include <vector>

namespace presentations {
struct ParsedElement;

class CodeParser {
  public:
    explicit CodeParser(CodeThemeConfig& config);

    [[nodiscard]] std::vector<ParsedElement> parse(const QString& code) const;

  private:
    CodeThemeConfig& m_config;
};

} // namespace presentations

#endif // PRESENTATIONS_CODE_PARSER_HPP
