#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "lexer.h" 
#include "ast.h"

int main() {
    FILE *file = fopen("exemple.intech", "r");
    if (file == NULL) {
        perror("Erreur lors de l'ouverture du fichier");
        return 1;
    }

    buffer_t buffer;
    buf_init(&buffer, file);

    // char *alphanum_rb = lexer_getalphanum_rollback(&buffer);
    // char *alphanum = lexer_getalphanum(&buffer);
    // char *op = lexer_getop(&buffer);
    // long num = lexer_getnumber(&buffer);
    // char *alphanum2 = lexer_getalphanum(&buffer);
    // char *op2 = lexer_getop(&buffer);
    
    

    // if (alphanum_rb != NULL) {
    //     printf("Chaine (ROLLBACK) trouvee : %s\n", alphanum_rb);
    //     free(alphanum_rb);
    // } else {
    //     printf("Pas de chaine (ROLLEBACK) trouvee.\n");
    // }

    // if (alphanum != NULL) {
    //     printf("Chaine 1 trouvee : %s\n", alphanum);
    //     free(alphanum);
    // } else {
    //     printf("Pas de chaine 1 trouvee.\n");
    // }

    //  if (op != NULL) {
    //     printf("Chaine (OP) trouvee : %s\n", op);
    //     free(op);
    // } else {
    //     printf("Pas de chaine (OP) trouvee.\n");
    // }

    // if (num >= 0) {
    //     printf("Chaine_nb trouvee : %d\n", num);
    // } else {
    //     printf("Pas de chaine_nb trouvee.\n");
    // }

    // if (alphanum2 != NULL) {
    //     printf("Chaine 2 trouvee : %s\n", alphanum2);
    //     free(alphanum2);
    // } else {
    //     printf("Pas de chaine 2 trouvee.\n");
    // }

    // if (op2 != NULL) {
    //     printf("Chaine (OP2) trouvee : %s\n", op2);
    //     free(op2);
    // } else {
    //     printf("Pas de chaine (OP2) trouvee.\n");
    // }
    ast_t *intNode = ast_new_integer(50);
    ast_t *intNode2 = ast_new_integer(2);
    ast_t *intNode3 = ast_new_integer(30);
    ast_t *unaNode = ast_new_unary(ADDITION, intNode);
    ast_list_t *node1 = ast_list_new_node(intNode);
    printf("\n1) : ");
    print_ast_list(node1);
    ast_list_add(&node1, intNode);
    printf("\n2) : ");
    print_ast_list(node1);
    ast_list_add(&node1, intNode2);
    printf("\n3) : ");
    print_ast_list(node1);

    // printf("(INTEGER) Type = %s | value = %ld", ast_node_type_to_string(intNode->type), intNode->integer);
    // printf("(UNARY) Type = %s | Expression = %ld", ast_node_type_to_string(unaNode->type), unaNode->unary.operand->integer);
    
    
    fclose(file);

    return 0;
}
