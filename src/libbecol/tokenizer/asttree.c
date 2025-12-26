#include "../config.h"
#include "asttree.h"
#include "../memory/mem.h"
#include <stddef.h>
#include <stdio.h>

// utility file for stuff relating to AST Tree stuff.

#ifdef INCLUDE_ASTTREE_TOKEN_NAMES
char* ASTTreeTypeNames[] = {
    "Program",
    "Action",
    "Request",
    "Tell",
    
    "Literal",
    "Variable",
    "Grouping",

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

ASTTreeNode* BecolMallocASTNode() {
    ASTTreeNode* node = BecolMalloc(sizeof(ASTTreeNode));
    node->arguments = NULL;
    node->child_nodes = NULL;
    node->num_of_arguments = 0;
    node->num_of_child_nodes = 0;
    return node;
}

void BecolFreeASTNode(ASTTreeNode* node) {
    if (node == NULL)
        return;
    BecolFree(node->arguments);
    BecolFree(node->child_nodes);
    BecolFree(node);
}

void _BecolPrintASTTree(ASTTreeNode* root, int indent) {
    printf("%s\n", BecolGetTypeNameFromASTType(root->type));
    for (int i=0;i<root->num_of_child_nodes;i++) {
        _BecolPrintASTTree(root->child_nodes[i], indent+4);
    }
}
void BecolPrintASTTree(ASTTreeNode* root) {
    _BecolPrintASTTree(root, 0);
}
