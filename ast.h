#ifndef AST_H
#define AST_H

#include <memory>
#include <stdexcept>
#include <cmath>

struct Expr {
    virtual ~Expr() = default;
    virtual double eval() const = 0;
};

struct NumberExpr : Expr {
    double value;
    explicit NumberExpr(double v) : value(v) {}
    double eval() const override { return value; }
};

enum BinOp { OP_ADD, OP_SUB, OP_MUL, OP_DIV };

struct BinaryExpr : Expr {
    std::unique_ptr<Expr> left, right;
    BinOp op;

    BinaryExpr(std::unique_ptr<Expr> l, BinOp o, std::unique_ptr<Expr> r)
        : left(std::move(l)), right(std::move(r)), op(o) {}

    double eval() const override {
        switch (op) {
            case OP_ADD: return left->eval() + right->eval();
            case OP_SUB: return left->eval() - right->eval();
            case OP_MUL: return left->eval() * right->eval();
            case OP_DIV: 
            if (right->eval() == 0.0) {
                throw std::runtime_error("Semantic error: division by zero");
            }
            return left->eval() / right->eval();
        }
        return 0;
    }
};

struct UnaryMinusExpr : Expr {
    std::unique_ptr<Expr> expr;
    explicit UnaryMinusExpr(std::unique_ptr<Expr> e) : expr(std::move(e)) {}
    double eval() const override { return -expr->eval(); }
};

#endif // AST_H
