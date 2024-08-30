#ifndef PARSE_H

// https://godbolt.org/z/bsndGaf3h

#include <stdint.h>

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

    struct {
        int flags;
        int type;

        union {
            void        _void;
            char        _char;
            short       _short;
            double      _double;
            int         _int;
            long        _long;
            long long   _long2;
        } Flavour;
    } BuiltinType;
} AstNode;

enum {
    _TYPE_VOID,
    _TYPE_CHAR,
    _TYPE_SHORT,
    _TYPE_DOUBLE,
    _TYPE_INT,
    _TYPE_LONG,
    _TYPE_LONG2,
    _TYPE_STRUCT,
    _TYPE_UNION,
};

enum {
    _BUILTIN_IS_SIGNED       = 1,
    _BUILTIN_IS_STATIC       = 2,
    _BUILTIN_IS_CONST        = 4,
    _BUILTIN_IS_POINTER      = 8,
    _BUILTIN_IS_ARRAY        = 16,
    _BUILTIN_IS_EXTERN       = 32,
    _BUILTIN_IS_RESTRICT     = 64,
};

#endif
