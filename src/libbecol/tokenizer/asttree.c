#include "../config.h"
#include "asttree.h"
#include "../memory/mem.h"

// utility file for stuff relating to AST Tree stuff.

#ifdef INCLUDE_ASTTREE_TOKEN_NAMES
char* ASTTreeTypeNames[] = {
    "Program",
    "Action",
    "Request",
    "Tell",
    
    "Litteral",
    "Variable",
    "Expr",

    "Add",
    "Sub",
    "Mul",
    "Div",
    "Mod",
    "Equal",
    "Greator",
    "Less",
    "GreaterOrEqual",
    "LessOrEqual",
    "NotEqual",
};
#endif

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

ASTTreeNode* BecolMallocASTNode(int num_of_child_nodes, int num_of_arguments) {
    ASTTreeNode* node = BecolMalloc(sizeof(ASTTreeNode));
    node->arguments = BecolMalloc(sizeof(void*)*num_of_arguments);
    node->child_nodes = BecolMalloc(sizeof(void*)*num_of_child_nodes);
    node->num_of_arguments = num_of_arguments;
    node->num_of_child_nodes = num_of_child_nodes;
    return node;
}

void BecolFreeASTNode(ASTTreeNode* node) {
    BecolFree(node->arguments);
    BecolFree(node->child_nodes);
    BecolFree(node);
}
