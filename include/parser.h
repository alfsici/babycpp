#pragma once
#include "lexer.h"
#include <unordered_map>
namespace babycpp {
namespace parser {

using lexer::Lexer;
using lexer::Number;

// base struct for all ast expr
struct ExprAST {
  virtual ~ExprAST() = default;
};

struct NumberExprAST : public ExprAST {
  NumberExprAST(Number val) : val(val) {}

  // keeping it public mainly for testabiliy purposes
  Number val;
};

struct VariableExprAST : public ExprAST {
  std::string name;
  VariableExprAST(const std::string &name) : name{name} {}
};

struct BinaryExprAST : public ExprAST {
  char op;
  ExprAST *lhs, *rhs;
  BinaryExprAST(char op, ExprAST *lhs, ExprAST *rhs)
      : op(op), lhs(lhs), rhs(rhs) {}
};

struct CallExprAST : public ExprAST {
  std::string callee;
  std::vector<ExprAST *> args;

  CallExprAST(const std::string &callee, std::vector<ExprAST *> &args)
      : callee(callee), args(args) {}
};

struct PrototypeAST {
  std::string name;
  std::vector<std::string> args;

  PrototypeAST(const std::string &name, const std::vector<std::string> &args)
      : name(name), args(args) {}
};

struct FunctionAST {
  PrototypeAST *proto;
  ExprAST *body;

  FunctionAST(PrototypeAST *proto, ExprAST *body) : proto(proto), body(body) {}
};

struct Argument {
  Argument(int datatype, std::string &argName)
      : type(datatype), name(argName) {}
  int type;
  std::string name;
};

struct Parser {
  explicit Parser(Lexer *inputLexer) : lex(inputLexer) {}

  NumberExprAST *parseNumber();
  ExprAST *parseIdentifier();
  ExprAST *parseExpression();
  ExprAST *parseBinOpRHS(int opPrec, ExprAST *LHS);
  ExprAST *parsePrimary();

  int getTokPrecedence();
  ExprAST *parseStatement();
  ExprAST *parseExtern();
  bool parseArguments(std::vector<Argument> &args);
  // this function defines whether or not a token is a declaration
  // token or not, meaning defining an external function or datatype
  // interesting to think of cating as "anonymous declaration maybe?"
  bool isDeclarationToken();
  bool isDatatype();
  const static std::unordered_map<char, int> BIN_OP_PRECEDENCE;
  Lexer *lex;
};

} // namespace parser
} // namespace babycpp
