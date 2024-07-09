#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include "ast.h"


ast_t *ast_new_integer (long val) {
  ast_t *intNode = (ast_t *)malloc(sizeof(ast_t));
    if (intNode == NULL) {
        fprintf(stderr, "Erreur d'allocation mémoire\n");
        exit(EXIT_FAILURE);
    }
    intNode->type = AST_INTEGER;
    intNode->integer = val;
    return intNode;
}