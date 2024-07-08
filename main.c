#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "lexer.h"  // Assurez-vous d'inclure votre en-tête de buffer et d'autres dépendances nécessaires

int main() {
    // Exemple avec un fichier
    FILE *file = fopen("exemple.txt", "r");
    if (file == NULL) {
        perror("Erreur lors de l'ouverture du fichier");
        return 1;
    }

    // Initialisation du buffer avec buf_init
    buffer_t buffer;
    buf_init(&buffer, file);

    // Appel de lexer_getalphanum
    char *alphanum_rb = lexer_getalphanum_rollback(&buffer);
    char *alphanum = lexer_getalphanum(&buffer);
    char *alphanum2 = lexer_getalphanum(&buffer);
    char *alphanum3 = lexer_getalphanum(&buffer);
    char *alphanum4 = lexer_getalphanum(&buffer);

    if (alphanum_rb != NULL) {
        printf("Chaine trouvee : %s\n", alphanum_rb);
        free(alphanum_rb);
    } else {
        printf("Pas de chaine trouvee.\n");
    }

    if (alphanum != NULL) {
        printf("Chaine trouvee : %s\n", alphanum);
        free(alphanum);
    } else {
        printf("Pas de chaine trouvee.\n");
    }

    if (alphanum2 != NULL) {
        printf("Chaine 2 trouvee : %s\n", alphanum2);
        free(alphanum2);
    } else {
        printf("Pas de chaine 2 trouvee.\n");
    }

    if (alphanum3 != NULL) {
        printf("Chaine 3 trouvee : %s\n", alphanum3);
        free(alphanum3);
    } else {
        printf("Pas de chaine 3 trouvee.\n");
    }

    if (alphanum4 != NULL) {
        printf("Chaine 4 trouvee : %s\n", alphanum4);
        free(alphanum4);
    } else {
        printf("Pas de chaine 4 trouvee.\n");
    }

    // Fermeture du fichier et nettoyage des ressources
    fclose(file);

    return 0;
}
