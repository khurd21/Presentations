#ifndef PRESENTATIONS_CODE_PARSER_HPP
#define PRESENTATIONS_CODE_PARSER_HPP

#include <presentations/CodeThemeConfig.hpp>

#include <vector>

namespace presentations {
struct ParsedElement;

/**
 * @class CodeParser
 * @brief The CodeParser class parses the code into a list of elements.
 */
class CodeParser {
  public:
    /**
     * @brief Construct a new CodeParser object.
     * @param config The code theme configuration.
     */
    explicit CodeParser(CodeThemeConfig& config);

    /**
     * @brief Parses the code into chunks of parsed element objects.
     * @param code The code to parse.
     * @return The list of parsed elements.
     */
    [[nodiscard]] std::vector<ParsedElement> parse(const QString& code) const;

  private:
    CodeThemeConfig& m_config;
};

} // namespace presentations

#endif // PRESENTATIONS_CODE_PARSER_HPP
