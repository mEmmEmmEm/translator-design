#ifndef PARSER_H
#define PARSER_H

#include "lexer.h"
#include "tokens.h"
#include "ast.h"

#include <memory>
#include <stdexcept>
#include <sstream>

class Parser {
private:
    Lexer& lexer;
    Token current;

    void next() {
        current = lexer.getNextToken();
    }

    void expect(TokenType t) {
        if (current.type != t) {
            std::ostringstream oss;
            oss << "Syntax error (" << current.lexeme << "'";
            throw std::runtime_error(oss.str());
        }
        next();
    }

    std::unique_ptr<Expr> parseFactor() {

        if (current.type == NUMBER) {
            double val = current.value;
            next();
            return std::make_unique<NumberExpr>(val);
        }

        if (current.type == LPAREN) {
            next();
            auto e = parseExpr();
            expect(RPAREN);
            return e;
        }

        if (current.type == MINUS) {
            next();
            return std::make_unique<UnaryMinusExpr>(parseFactor());
        }

        std::ostringstream oss;
        oss << "Error in the factor: unexpected token '" << current.lexeme << "'";
        throw std::runtime_error(oss.str());
    }

    std::unique_ptr<Expr> parseTerm() {
        auto left = parseFactor();

        while (current.type == MUL || current.type == DIV) {
            TokenType op = current.type;
            next();

            auto right = parseFactor();

            if (op == MUL)
                left = std::make_unique<BinaryExpr>(std::move(left), OP_MUL, std::move(right));
            else
                left = std::make_unique<BinaryExpr>(std::move(left), OP_DIV, std::move(right));
        }

        return left;
    }

    std::unique_ptr<Expr> parseExpr() {
        auto left = parseTerm();

        while (current.type == PLUS || current.type == MINUS) {
            TokenType op = current.type;
            next();

            auto right = parseTerm();

            if (op == PLUS)
                left = std::make_unique<BinaryExpr>(std::move(left), OP_ADD, std::move(right));
            else
                left = std::make_unique<BinaryExpr>(std::move(left), OP_SUB, std::move(right));
        }

        return left;
    }

public:
    Parser(Lexer& l) : lexer(l) {
        next(); 
    }

    double parseAndEval() {
        auto ast = parseExpr();

        if (current.type != TOKEN_EOF) {
            std::ostringstream oss;
            oss << "Extra input after the expression: '" << current.lexeme << "'";
            throw std::runtime_error(oss.str());
        }

        return ast->eval();
    }
};

#endif // PARSER_H
