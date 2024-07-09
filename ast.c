#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include "ast.h"


ast_t *ast_new_integer(long val) {
  ast_t *intNode = (ast_t *)malloc(sizeof(ast_t));
  if (intNode == NULL) {
    fprintf(stderr, "Erreur d'allocation mémoire\n");
    exit(EXIT_FAILURE);
  }
  intNode->type = AST_INTEGER;
  intNode->integer = val;
  return intNode;
}

ast_t *ast_new_variable(char *name, var_type_e type) {
  ast_t *varNode = (ast_t *)malloc(sizeof(ast_t));
  if (varNode == NULL) {
    fprintf(stderr, "Erreur d'allocation mémoire\n");
    exit(EXIT_FAILURE);
  }
  varNode->type = AST_VARIABLE;
  varNode->var.name = name;
  varNode->var.type = type;
  return varNode; 
}