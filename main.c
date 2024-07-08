#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "lexer.h" // Assurez-vous d'inclure votre en-tête de buffer et d'autres dépendances nécessaires

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
    char *alphanum = lexer_getalphanum(&buffer);
    if (alphanum != NULL) {
        printf("Chaine trouvee : %s\n", alphanum);
        free(alphanum); 
    } else {
        printf("Pas de chaine trouvee.\n");
    }

    // Fermeture du fichier et nettoyage des ressources
    fclose(file);

    return 0;
}
