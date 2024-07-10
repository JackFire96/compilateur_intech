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

ast_t *ast_new_binary(ast_binary_e op, ast_t *left, ast_t *right) {
  ast_t *binNode = (ast_t *)malloc(sizeof(ast_t));
  if (binNode == NULL) {
    fprintf(stderr, "Erreur d'allocation mémoire\n");
    exit(EXIT_FAILURE);
  }
  binNode->type = AST_BINARY;
  binNode->binary.op = op;
  binNode->binary.left = left;
  binNode->binary.right = right;
  return binNode;
}

ast_t *ast_new_unary(ast_unary_e op, ast_t *operand) {
  ast_t *unaNode = (ast_t *)malloc(sizeof(ast_t));
  if (unaNode == NULL) {
    fprintf(stderr, "Erreur d'allocation mémoire\n");
    exit(EXIT_FAILURE);
  }
  unaNode->type = AST_UNARY;
  unaNode->unary.op = op;
  unaNode->unary.operand = operand;
  return unaNode;
}

ast_t *ast_new_function (char *name, var_type_e return_type, ast_list_t *params, ast_list_t *stmts) {
  ast_t *funNode = (ast_t *)malloc(sizeof(ast_t));
  if (funNode == NULL) {
    fprintf(stderr, "Erreur d'allocation mémoire\n");
    exit(EXIT_FAILURE);
  }
  funNode->type = AST_FUNCTION;
  funNode->function.name = name;
  funNode->function.return_type = return_type;
  funNode->function.params = params;
  funNode->function.stmts = stmts;
  return funNode; 
}

ast_t *ast_new_fncall (char *name, ast_list_t *args) {
  ast_t *fncNode = (ast_t *)malloc(sizeof(ast_t));
  if (fncNode == NULL) {
    fprintf(stderr, "Erreur d'allocation mémoire\n");
    exit(EXIT_FAILURE);
  }
  fncNode->type = AST_FNCALL;
  fncNode->call.name = name;
  fncNode->call.args = args;
  return fncNode; 
}

ast_t *ast_new_comp_stmt (ast_list_t *stmts) {
  ast_t *compNode = (ast_t *)malloc(sizeof(ast_t));
  if (compNode == NULL) {
    fprintf(stderr, "Erreur d'allocation mémoire\n");
    exit(EXIT_FAILURE);
  }
  compNode->type = AST_COMPOUND_STATEMENT;
  compNode->compound_stmt.stmts = stmts;
  return compNode; 
}

ast_t *ast_new_assignment (ast_t *lvalue, ast_t *rvalue) {
  ast_t *assNode = (ast_t *)malloc(sizeof(ast_t));
  if (assNode == NULL) {
    fprintf(stderr, "Erreur d'allocation mémoire\n");
    exit(EXIT_FAILURE);
  }
  assNode->type = AST_ASSIGNMENT;
  assNode->assignment.lvalue = lvalue;
  assNode->assignment.rvalue = rvalue;
  return assNode; 
}

ast_t *ast_new_declaration (ast_t *lvalue, ast_t *rvalue) {
  ast_t *decNode = (ast_t *)malloc(sizeof(ast_t));
  if (decNode == NULL) {
    fprintf(stderr, "Erreur d'allocation mémoire\n");
    exit(EXIT_FAILURE);
  }
  decNode->type = AST_DECLARATION;
  decNode->declaration.lvalue = lvalue;
  decNode->declaration.rvalue = rvalue;
  return decNode; 
}

ast_t *ast_new_condition (ast_t *condition, ast_t *valid, ast_t *invalid) {
  ast_t *conNode = (ast_t *)malloc(sizeof(ast_t));
  if (conNode == NULL) {
    fprintf(stderr, "Erreur d'allocation mémoire\n");
    exit(EXIT_FAILURE);
  }
  conNode->type = AST_CONDITION;
  conNode->branch.condition = condition;
  conNode->branch.valid = valid;
  conNode->branch.invalid = invalid;
  return conNode; 
}

ast_t *ast_new_loop (ast_t *condition, ast_t *stmt) {
  ast_t *looNode = (ast_t *)malloc(sizeof(ast_t));
  if (looNode == NULL) {
    fprintf(stderr, "Erreur d'allocation mémoire\n");
    exit(EXIT_FAILURE);
  }
  looNode->type = AST_LOOP;
  looNode->loop.condition = condition;
  looNode->loop.stmt = stmt;
  return looNode; 
}

ast_t *ast_new_return (ast_t *expr) {
  ast_t *retNode = (ast_t *)malloc(sizeof(ast_t));
  if (retNode == NULL) {
    fprintf(stderr, "Erreur d'allocation mémoire\n");
    exit(EXIT_FAILURE);
  }
  retNode->type = AST_RETURN;
  retNode->ret.expr = expr;
  return retNode; 
}

ast_list_t *ast_list_new_node (ast_t *elem) {
  ast_list_t *node = (ast_list_t *)malloc(sizeof(ast_list_t));
  node->node = elem;
  node->next = NULL;
  return node;
}

void ast_list_add (ast_list_t **list, ast_t *elem) {
  ast_list_t *node = ast_list_new_node(elem);
    if (*list == NULL) {
        *list = node;
    } else {
        ast_list_t *current = *list;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = node;
    }
}

const char* ast_node_type_to_string(ast_node_type_e type) {
    switch (type) {
        case AST_VOID: return "AST_VOID";
        case AST_INTEGER: return "AST_INTEGER";
        case AST_BINARY: return "AST_BINARY";
        case AST_UNARY: return "AST_UNARY";
        case AST_FUNCTION: return "AST_FUNCTION";
        case AST_FNCALL: return "AST_FNCALL";
        case AST_VARIABLE: return "AST_VARIABLE";
        case AST_CONDITION: return "AST_CONDITION";
        case AST_LOOP: return "AST_LOOP";
        case AST_DECLARATION: return "AST_DECLARATION";
        case AST_ASSIGNMENT: return "AST_ASSIGNMENT";
        case AST_COMPOUND_STATEMENT: return "AST_COMPOUND_STATEMENT";
        case AST_RETURN: return "AST_RETURN";
        default: return "UNKNOWN_TYPE";
    }
}

void print_ast_list(ast_list_t *list) {
    while (list != NULL) {
        ast_t *node = list->node;
        printf("Node type: %s\n", ast_node_type_to_string(node->type));
        list = list->next;
    }
}