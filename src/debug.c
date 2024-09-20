#include <stdio.h>

#include "nasal.h"
#include "data.h"
#include "code.h"

const char* opcodeNames[] = {
    "OP_NOT",
    "OP_MUL",
    "OP_PLUS",
    "OP_MINUS",
    "OP_DIV",
    "OP_NEG",
    "OP_CAT",
    "OP_LT",
    "OP_LTE",
    "OP_GT",
    "OP_GTE",
    "OP_EQ",
    "OP_NEQ",
    "OP_EACH",
    "OP_JMP",
    "OP_JMPLOOP",
    "OP_JIFNOTPOP",
    "OP_JIFEND",
    "OP_FCALL",
    "OP_MCALL",
    "OP_RETURN",
    "OP_PUSHCONST",
    "OP_PUSHONE",
    "OP_PUSHZERO",
    "OP_PUSHNIL",
    "OP_POP",
    "OP_DUP",
    "OP_XCHG",
    "OP_INSERT",
    "OP_EXTRACT",
    "OP_MEMBER",
    "OP_SETMEMBER",
    "OP_LOCAL",
    "OP_SETLOCAL",
    "OP_NEWVEC",
    "OP_VAPPEND",
    "OP_NEWHASH",
    "OP_HAPPEND",
    "OP_MARK",
    "OP_UNMARK",
    "OP_BREAK",
    "OP_SETSYM",
    "OP_DUP2",
    "OP_INDEX",
    "OP_BREAK2",
    "OP_PUSHEND",
    "OP_JIFTRUE",
    "OP_JIFNOT",
    "OP_FCALLH",
    "OP_MCALLH",
    "OP_XCHG2",
    "OP_UNPACK",
    "OP_SLICE",
    "OP_SLICE2",
    "OP_BIT_AND",
    "OP_BIT_OR",
    "OP_BIT_XOR",
    "OP_BIT_NEG"
};

const char* getOpcodeNames(int opcode) {
    if (opcode < 0 || opcode >= sizeof(opcodeNames) / sizeof(opcodeNames[0]) || opcodeNames[opcode] == NULL) {
        return "UNKNOWN_OPCODE";
    }
    return opcodeNames[opcode];
}

void printNaStr(struct naStr* str) {
    if (str == NULL) {
        printf("str: <null string>");
    } else if (str->emblen != -1) {
        // String is embedded (use buf)
        printf("str: %.*s", str->emblen, (char*)str->data.buf);
    } else if (str->data.ref.ptr == NULL) {
        // External string pointer is null
        printf("str: <empty string>");
    } else {
        // Print the string from the external pointer
        printf("%s", str->data.ref.ptr);
    }
}


// Example function to print a naVec object
void printNaVec(struct naVec* vec) {
    printf("<vector>");  // Placeholder, implement vector printing logic here
}

// Example function to print a naHash object
void printNaHash(struct naHash* hash) {
    printf("<hash>");  // Placeholder, implement hash printing logic here
}

// Function to print a naRef using the provided macros
void printNaRef(naRef ref) {
    if (IS_NUM(ref)) {
        // It's a number
        printf("num: %f", ref.num);
    } else if (IS_NIL(ref)) {
        // It's a nil reference
        printf("nil");
    } else if (IS_STR(ref)) {
        // It's a string
        printNaStr(PTR(ref).str);
    } else if (IS_VEC(ref)) {
        // It's a vector
        printNaVec(PTR(ref).vec);
    } else if (IS_HASH(ref)) {
        // It's a hash
        printNaHash(PTR(ref).hash);
    } else if (IS_CODE(ref)) {
        printf("<code>");
    } else if (IS_FUNC(ref)) {
        printf("<function>");
    } else if (IS_CCODE(ref)) {
        printf("<C function>");
    } else if (IS_GHOST(ref)) {
        printf("<ghost>");
    } else {
        printf("<unknown object>");
    }
}

// Function to print the opStack
void printOperandStack(naContext ctx) {  // Use naContext, which is a typedef for struct Context*
    printf("Operand Stack (top = %d):\n", ctx->opTop);

    for (int i = 0; i < ctx->opTop; ++i) {
        printf("  [%d]: ", i);
        printNaRef(ctx->opStack[i]);  // Print each naRef in the stack
        printf("\n");
    }
}
