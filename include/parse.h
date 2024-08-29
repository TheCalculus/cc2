#ifndef PARSE_H

// https://godbolt.org/z/bsndGaf3h

struct AstNode;

typedef
struct AstNode {
    union {
        struct VarDecl;

        struct FunctionDecl;
        struct ParamVarDecl;
    } DeclStmt;

    struct ImplicitCast;
    struct ExplicitCast;

    struct ReturnStmt;

    struct CallExpr;

    struct BinaryExp;
    struct Unary;
} AstNode;

#endif
