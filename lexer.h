#ifndef LEXER_H
#define LEXER_H

#include "tokens.h"
#include <istream>
#include <cctype>
#include <stdexcept>

class Lexer {
    std::istream& in;
    int ch = ' ';

    void advance() { ch = in.get(); }

public:
    explicit Lexer(std::istream& i) : in(i) { advance(); }

    Token getNextToken() {
        while (isspace(ch)) advance();

        if (ch == EOF) return Token(TOKEN_EOF);

        if (isdigit(ch) || ch == '.') {
            std::string num;
            while (isdigit(ch) || ch == '.' || ch == 'e' || ch == 'E' || ch == '+' || ch == '-') {
                num += char(ch);
                advance();
            }
            return Token(NUMBER, num, std::stod(num));
        }

        char c = ch;
        advance();

        switch (c) {
            case '+': return Token(PLUS, "+");
            case '-': return Token(MINUS, "-");
            case '*': return Token(MUL, "*");
            case '/': return Token(DIV, "/");
            case '(': return Token(LPAREN, "(");
            case ')': return Token(RPAREN, ")");
        }

        throw std::runtime_error("Unknown symbol: " + std::string(1, c));
    }
};

#endif // LEXER_H
