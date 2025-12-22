#include "../config.h"
#include "asttree.h"

// utility file for stuff relating to AST Tree stuff.

// if we have the token names, use them. Else just use the number of the token
char* BecolGetTypeNameFromASTType(ASTTreeType type) {
#ifdef INCLUDE_ASTTREE_TOKEN_NAMES 
    return ASTTreeTypeNames[type];
#else
    char ret[5];
    snprintf(ret, 5, "%d", type);
    return ret;
#endif
}
