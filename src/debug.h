#include "code.h"

/**
 * @def DEBUG
 * @brief A macro for executing debug code conditionally based on NASAL_DEBUG.
 *
 * This macro will execute the code passed to it only if the `NASAL_DEBUG`
 * macro is defined. If `NASAL_DEBUG` is not defined, the macro expands
 * to nothing, and the code is excluded from the compiled output.
 *
 * @param code The block of code to execute when `NASAL_DEBUG` is defined.
 */

/**
 * @def DEBUG_LOG
 * @brief A macro for printing debug statements conditionally based on NASAL_DEBUG.
 *
 * This macro will print the string passed to it only if the `NASAL_DEBUG`
 * macro is defined. If `NASAL_DEBUG` is not defined, the macro expands
 * to nothing, and the code is excluded from the compiled output.
 *
 * @param code The block of code to execute when `NASAL_DEBUG` is defined.
 */

 #ifdef NASAL_DEBUG
  #include <stdio.h>
  #define DEBUG_LOG(fmt, ...) fprintf(stderr, "DEBUG: " fmt "\n", ##__VA_ARGS__)
  #define DEBUG(code) do { code; } while(0)
#else
  #define DEBUG_LOG(fmt, ...) // No-op
  #define DEBUG(code) do {} while(0)
#endif


const char* getOpcodeNames(int opcode);
void printOperandStack(naContext ctx);