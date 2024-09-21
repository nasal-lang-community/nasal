#ifndef _PARSE_H
#define _PARSE_H

#include <setjmp.h>

#include "nasal.h"
#include "data.h"
#include "code.h"

/**
 * @enum Tokens
 * @brief This enum contains all of the tokens recognized by Nasal.
 */
enum tok {
    TOK_TOP = 1,
    /**
     * @brief This token represents the logical `and` operator, which corresponds to the lexeme of the same name in Nasal.
     */
    TOK_AND,
    /**
     * @brief This token represents the logical `or` operator, which corresponds to the lexeme of the same name in Nasal.
     */
    TOK_OR,
    /**
     * @brief This token represents the logical NOT operator, which corresponds to the `!` lexeme in Nasal.
     */
    TOK_NOT,
    /**
     * @brief This token represents the bitwise AND operator, which corresponds to a single `&` lexeme in Nasal.
     */
    TOK_BIT_AND,
    /**
     * @brief This token represents the bitwise OR operator, which corresponds to a single `|` lexeme in Nasal.
     */
    TOK_BIT_OR,
    /**
     * @brief This token represents the bitwise XOR operator, which corresponds to the `^` lexeme in Nasal.
     */
    TOK_BIT_XOR,
    /**
     * @brief This token represents the bitwise negation operator, which corresponds to the `-` lexeme in Nasal.
     */
    TOK_BIT_NEG,
    /**
     * @brief This token represents the opening (or left) parenthesis, which corresponds to the `(` lexeme in Nasal.
     */
    TOK_LPAR,
    /**
     * @brief This token represents the closing (or right) parenthesis, which corresponds to the `)` lexeme in Nasal.
     */
    TOK_RPAR,
    /**
     * @brief This token represents the opening (or left) bracket, which corresponds to the `[` lexeme in Nasal.
     */
    TOK_LBRA,
    /**
     * @brief This token represents the closing (or right) bracket, which corresponds to the `]` lexeme in Nasal.
     */
    TOK_RBRA,
    /**
     * @brief This token represents the opening (or left) curly bracket, which corresponds to the `{` lexeme in Nasal.
     */
    TOK_LCURL,
    /**
     * @brief This token represents the closing (or right) curly bracket, which corresponds to the `}` lexeme in Nasal.
     */
    TOK_RCURL,
    /**
     * @brief This token represents the multiplication operator, which corresponds to the `*` lexeme in Nasal.
     */
    TOK_MUL,
    /**
     * @brief This token represents the addition operator, which corresponds to the `+` lexeme in Nasal.
     */
    TOK_PLUS,
    /**
     * @brief This token represents the subtraction operator, which corresponds to the `-` lexeme in Nasal.
     */
    TOK_MINUS,
    /**
     * @brief This token represents the negation operator, which corresponds to the `-` lexeme in Nasal.
     */
    TOK_NEG,
    /**
     * @brief This token represents the division operator, which corresponds to the `/` lexeme in Nasal.
     */
    TOK_DIV,
    /**
     * @brief This token represents the string concatenation operator, which corresponds to the `~` lexeme in Nasal.
     */
    TOK_CAT,
    /**
     * @brief This token represents the colon, which corresponds to the `:` lexeme in Nasal.
     */
    TOK_COLON,
    /**
     * @brief This token represents the period, which corresponds to the `.` lexeme in Nasal.
     */
    TOK_DOT,
    /**
     * @brief This token represents the comma, which corresponds to the `,` lexeme in Nasal.
     */
    TOK_COMMA,
    /**
     * @brief This token represents the semicolon, which corresponds to the `;` lexeme in Nasal.
     */
    TOK_SEMI,
    /**
     * @brief This token represents the assignment operator, which corresponds to the `=` lexeme in Nasal.
     */
    TOK_ASSIGN,
    /**
     * @brief This token represents the less than relational operator, which corresponds to the `<` lexeme in Nasal.
     */
    TOK_LT,
    /**
     * @brief This token represents the less than or equal to relational operator, which corresponds to the `<=` lexeme in Nasal.
     */
    TOK_LTE,
    /**
     * @brief This token represents the equality operator, which corresponds to the `==` lexeme in Nasal.
     */
    TOK_EQ,
    /**
     * @brief This token represents the not equals operator, which corresponds to the `!=` lexeme in Nasal.
     */
    TOK_NEQ,
    /**
     * @brief This token represents the greater than relational operator, which corresponds to the `>` lexeme in Nasal.
     */
    TOK_GT,
    /**
     * @brief This token representsents the greater than or equal to relational operator, which corresponds to the `>=` lexeme in Nasal.
     */
    TOK_GTE,
    /**
     * @brief This token represents the conditonal `if` statement, which corresponds to the lexeme of the same name in Nasal.
     */
    TOK_IF,
    /**
     * @brief This token represents the conditonal else-if statement, which corresponds to the `elsif` lexeme in Nasal.
     */
    TOK_ELSIF,
    /**
     * @brief This token represents the conditonal `else` statement, which corresponds to the lexeme of the same name in Nasal.
     */
    TOK_ELSE,
    /**
     * @brief This token represents the loop construct `for`, which corresponds to the lexeme of the same name in Nasal.
     */
    TOK_FOR,
    /**
     * @brief This token represents the loop construct `foreach`, which corresponds to the lexeme of the same name in Nasal.
     */
    TOK_FOREACH,
    /**
     * @brief This token represents the loop construct `while`, which corresponds to the lexeme of the same name in Nasal.
     */
    TOK_WHILE,
    /**
     * @brief This token represents the `return` statement, which corresponds to the lexeme of the same name in Nasal.
     */
    TOK_RETURN,
    /**
     * @brief This token represents the `break` statement, which corresponds to the lexeme of the same name in Nasal.
     */
    TOK_BREAK,
    /**
     * @brief This token represents the `continue` control flow statement, which corresponds to the lexeme of the same name in Nasal.
     */
    TOK_CONTINUE,
    /**
     * @brief This token represents the function definition construct, which corresponds to the `func` lexeme in Nasal.
     */
    TOK_FUNC,
    /**
     * @brief This is a special token type that does not correspond to a single lexeme, but rather represents identifiers such as variable or function name in Nasal.
     */
    TOK_SYMBOL,
    /**
     * @brief This is a special token type that represents literal values, such as numbers, strings, or other constant values in Nasal.
     */
    TOK_LITERAL,
    /**
     * @brief This is a special token type that does not correspond to a single character, but rather represents an empty token that has yet to be assigned to a lexeme in Nasal.
     */
    TOK_EMPTY,
    /**
     * @brief This token represents the `nil` literal, which corresponds to the absence of a value or "nothing" in Nasal.
     */
    TOK_NIL,
    /**
     * @brief This token represents the boolean value true, corresponding to the true lexeme in Nasal.
     */
    TOK_TRUE,
    /**
     * @brief This token represents the boolean value false, corresponding to the false lexeme in Nasal.
     */
    TOK_FALSE,
    /**
     * @brief This token represents the `...` (ellipsis), which is used to handle variadic arguments in Nasal functions.
     */
    TOK_ELLIPSIS,
    /**
     * @brief This token represents the ternary operator, which corresponds to the `?` lexeme in Nasal.
     */
    TOK_QUESTION,
    /**
     * @brief This token represents the `var` keyword, which is used for variable declaration in Nasal.
     */
    TOK_VAR,
    /**
     * @brief This token represents the `+=` operator, which performs addition and assignment in Nasal.
     */
    TOK_PLUSEQ,
    /**
    * @brief This token represents the `-=` operator, which performs subtraction and assignment in Nasal.
    */
    TOK_MINUSEQ,
    /**
     * @brief This token represents the `*=` operator, which performs multiplication and assignment in Nasal.
     */
    TOK_MULEQ,
    /**
     * @brief This token represents the `*=` operator, which performs multiplication and assignment in Nasal.
     */
    TOK_DIVEQ,
    /**
     * @brief This token represents the `~=` operator, which performs string concatenation and assignment in Nasal.
     */
    TOK_CATEQ,
    /**
     * @brief This token represents the `&=` operator, which performs bitwise AND and assignment in Nasal.
     */
    TOK_BIT_ANDEQ,
    /**
    * @brief This token represents the nullish coalescing operator (`??`), which returns the left-hand expression if it is not `nil`, otherwise it evaluates and returns the right-hand expression in Nasal.
    */
    TOK_NULL_CHAIN,
    /**
    * @brief This token represents the null access operator (`?`), which safely accesses properties or methods in Nasal by returning `nil` if the object is `nil`.
    */
    TOK_NULL_ACCESS,
    /**
     * @brief This token represents the `|=` operator, which performs bitwise OR and assignment in Nasal.
     */
    TOK_BIT_OREQ,
    /**
     * @brief This token represents the `^=` operator, which performs bitwise XOR and assignment in Nasal.
     */
    TOK_BIT_XOREQ,
    /**
     * @brief This token represents the `forindex` loop construct in Nasal.
     */
    TOK_FORINDEX
};

// Precedence rules
enum { PREC_BINARY=1, PREC_REVERSE, PREC_PREFIX, PREC_SUFFIX };

struct Token {
    enum tok type;
    int line;
    char* str;
    int strlen;
    int rule;
    double num;
    struct Token* next;
    struct Token* prev;
    struct Token* children;
    struct Token* lastChild;
};

struct Parser {
    // Handle to the Nasal interpreter
    struct Context* context;

    char* err;
    int errLine;
    jmp_buf jumpHandle;

    // The parse tree ubernode
    struct Token tree;

    // The input buffer
    char* buf;
    int   len;

    // Input file parameters (for generating pretty stack dumps)
    naRef srcFile;
    int firstLine;

    // Chunk allocator.  Throw away after parsing.
    void** chunks;
    int* chunkSizes;
    int nChunks;
    int leftInChunk;

    // Computed line number table for the lexer
    int* lines;
    int  nLines;

    struct CodeGenerator* cg;
};

/**
* @brief Array containing the accumulated bytecode, that is dynamically resized by emit().
*/
typedef unsigned short ByteCodeArray;

/**
 * @brief Manages the state of the code generation process.
 *
 * It contains fields that store the current bytecode buffer, the size of the bytecode array,
 * and the number of allocated entries. Functions that generate and emit bytecode operate
 * on this struct during the parsing phase.
 */
struct CodeGenerator {
    int lastLine;

    /**
    * @brief Array containing the accumulated bytecode, that is dynamically resized by emit().
    */
    ByteCodeArray* byteCode;
    int codesz;
    int codeAlloced;

    // Inst. -> line table, stores pairs of {ip, line}
    unsigned short* lineIps;
    int nLineIps; // number of pairs
    int nextLineIp;

    int* argSyms;
    int* optArgSyms;
    int* optArgVals;
    naRef restArgSym;

    // Stack of "loop" frames for break/continue statements
    struct {
        int breakIP;
        int contIP;
        struct Token* label;
    } loops[MAX_MARK_DEPTH];
    int loopTop;

    // Dynamic storage for constants, to be compiled into a static table
    naRef consts;
};

void naParseError(struct Parser* p, char* msg, int line);
void naParseInit(struct Parser* p);
void* naParseAlloc(struct Parser* p, int bytes);
void naParseDestroy(struct Parser* p);
void naLex(struct Parser* p);
int naLexUtf8C(char* s, int len, int* used); /* in utf8lib.c */
naRef naCodeGen(struct Parser* p, struct Token* block, struct Token* arglist);

void naParse(struct Parser* p);



#endif // _PARSE_H
