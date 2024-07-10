#ifndef SYMBOL_H

#include "ast.h"


typedef enum {
  INT,
  VOID
} sym_type_t;

typedef struct sym_entry_t {
  char *name;
  sym_type_t type;
  struct sym_entry_t *next;
} sym_entry_t;

typedef struct sym_table_t {
  sym_entry_t *root;
} sym_t;


sym_table_t * sym_new (char *name, sym_type_t type, ast_t *attributes);
void sym_delete (sym_table_t * sym);
void sym_remove (sym_table_t **table, sym_table_t *sym);
void sym_add (sym_table_t **table, sym_table_t *sym);
sym_table_t * sym_search (sym_table_t *table, char *name);


#define SYMBOL_H
#endif