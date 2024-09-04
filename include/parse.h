#ifndef PARSE_H
#define PARSE_H

// https://godbolt.org/z/bsndGaf3h

#include <stdint.h>

#include "general.h"

typedef struct {
    Vector ast;
} Parser;

typedef enum {
    _TYPE_VOID,
    _TYPE_CHAR,
    _TYPE_SHORT,
    _TYPE_DOUBLE,
    _TYPE_INT,
    _TYPE_LONG,
    _TYPE_LONG2,
    _TYPE_STRUCT,
    _TYPE_UNION,
} DataType;

enum {
    _BUILTIN_IS_SIGNED       = 1,
    _BUILTIN_IS_STATIC       = 2,
    _BUILTIN_IS_CONST        = 4,
    _BUILTIN_IS_POINTER      = 8,
    _BUILTIN_IS_ARRAY        = 16,
    _BUILTIN_IS_EXTERN       = 32,
    _BUILTIN_IS_RESTRICT     = 64,
};

typedef struct {
    int flags; // signed, static, const, ptr, arr, extern, restrict

    union {
        char        _char;
        short       _short;
        double      _double;
        int         _int;
        long        _long;
        long long   _long2;
    } Flavour;

    DataType type;
} BuiltinType;

typedef enum {
    VAR_DECL,
    FUNCTION_DECL,
    PARAM_VAR_DECL,
    EXPLICIT_CAST,
    RETURN_STMT,
    CALL_EXPR,
    BINARY_EXPR,
    UNARY,
} AstNodeType;

struct AstNode;

typedef
struct AstNode {
    char identifier[64];
    AstNodeType type;

    union {
        union {
            // TODO: multiple variable declaration
            struct {
                BuiltinType type;
                struct AstNode* init;
            } VarDecl;

            // TODO: vaargs
            struct {
                BuiltinType ret;

                struct AstNode* args;
                struct AstNode* body;
            } FunctionDecl;

            struct {
                BuiltinType type; 
            } ParamVarDecl;
        } DeclStmt;

        // also implicit
        struct {
            BuiltinType from;
            BuiltinType to;
            struct AstNode* on;
        } ExplicitCast;

        struct {
        } ReturnStmt;

        struct {
        } CallExpr;

        struct {
        } BinaryExpr;

        struct {
        } Unary;
    };
} AstNode;

void thicc_parse_tokens();

#endif
