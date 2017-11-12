#pragma once
#include <unordered_map>

namespace babycpp {
namespace diagnostic {

enum class IssueType { NONE = -1, LEXER = 0, PARSER, AST, CODEGEN };

enum class IssueCode {
  NONE = -1,

  // 0-999 lexer codes

  // 1000-1999 parser codes
  MISSING_OPEN_ROUND_OR_COMMA_IN_FUNC_CALL = 1000,
  MISSING_ARG_IN_FUNC_CALL = 1001,
  EXPECTED_VARIABLE = 1002,
  UNEXPECTED_TOKEN_IN_EXPRESSION = 1003,
  EXPECTED_END_STATEMENT_TOKEN = 1004,
  EXPECTED_TYPE_AFTER_EXTERN = 1005,
  EXPECTED_DATATYPE_FUNCTION_ARG = 1006,
  EXPECTED_IDENTIFIER_NAME = 1007,
  EXPECTED_TOKEN= 1008,
  EXPECTED_RETURN_DATATYPE = 1009,
	// 2000-2999 code gen codes
};

/**
 * \brief map from code to string representation of IssueType
 */
static const std::unordered_map<IssueType, std::string> issueTypeLookUp{
    {IssueType::NONE, "NONE"},
    {IssueType::LEXER, "LEXER"},
    {IssueType::PARSER, "PARSER"},
    {IssueType::AST, "AST"},
    {IssueType::CODEGEN, "CODEGEN"}};
/**
 * \brief map from code to IssueCode string representation
 */
static const std::unordered_map<IssueCode, std::string> issueCodeLookUp{

    {IssueCode::MISSING_OPEN_ROUND_OR_COMMA_IN_FUNC_CALL,
     "MISSING_OPEN_ROUND_OR_COMMA_IN_FUNC_CALL"},
    {IssueCode::MISSING_ARG_IN_FUNC_CALL, "MISSING_ARG_IN_FUNC_CALL"},
    {IssueCode::EXPECTED_VARIABLE, "EXPECTED_VARIABLE"},
    {IssueCode::UNEXPECTED_TOKEN_IN_EXPRESSION,
     "UNEXPECTED_TOKEN_IN_EXPRESSION"},
    {IssueCode::EXPECTED_END_STATEMENT_TOKEN, "EXPECTED_END_STATEMENT_TOKEN"},
    {IssueCode::EXPECTED_TYPE_AFTER_EXTERN, "EXPECTED_TYPE_AFTER_EXTERN"},
    {IssueCode::EXPECTED_DATATYPE_FUNCTION_ARG,
     "EXPECTED_DATATYPE_FUNCTION_ARG"},
    {IssueCode::EXPECTED_IDENTIFIER_NAME,
     "EXPECTED_DATATYPE_FUNCTION_ARG"},
    {IssueCode::EXPECTED_TOKEN,
     "EXPECTED_TOKEN"},
    {IssueCode::EXPECTED_RETURN_DATATYPE,
     "EXPECTED_RETURN_DATATYPE"},

};

} // namespace diagnostic
} // namespace babycpp