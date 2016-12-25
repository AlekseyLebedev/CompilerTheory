#pragma once

namespace IRTree {

    enum RELOP
    {
        // Arithmetic
        BINOP_PLUS,
        BINOP_MINUS,
        BINOP_MUL,
        BINOP_DIV,
		BINOP_MOD,

        // Bool
        BINOP_AND,
        BINOP_OR,
        BINOP_XOR,
        BINOP_LSHIFT,
        BINOP_RSHIFT,
        BINOP_ARSHIFT,

        // Logic
        CJUMP_EQ,
        CJUMP_NE,
        CJUMP_LT,
        CJUMP_GT,
        CJUMP_LE,
        CJUMP_GE,
        CJUMP_ULT,
        CJUMP_ULE,
        CJUMP_UGT,
        CJUMP_UGE,

        // Bool
        IRT_TRUE,
        IRT_FALSE

    };
}
