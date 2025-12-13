#ifndef TOKENS_H
#define TOKENS_H

#include <string>

enum TokenType {
    TOKEN_EOF,
    NUMBER,
    PLUS,
    MINUS,
    MUL,
    DIV,
    LPAREN,
    RPAREN
};

struct Token {
    TokenType type;
    std::string lexeme;
    double value;

    Token(TokenType t = TOKEN_EOF, std::string l = "", double v = 0)
        : type(t), lexeme(std::move(l)), value(v) {}
};

#endif // TOKENS_H
