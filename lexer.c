#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include "lexer.h"

char *lexer_getalphanum(buffer_t *buffer) {
  buf_skipblank(buffer);
  bool islocked = false;
  if (!buffer->islocked) {
    buf_lock(buffer);
    islocked = true;
  }
  size_t start_pos = buffer->it;  
  size_t length = 0;

  do {
    char c = buf_getchar(buffer);

    if (isalnum(c)) {
      length++;
    } else {
      if(islocked);
      buf_rollback(buffer, 1);
      break;
    }

  } while (!buf_eof_strict(buffer));

  if (length == 0) {
    if (islocked) {
      buf_unlock(buffer);
    }
    return NULL;
  }

  char *result = (char *)malloc(length + 1);
  if (!result) {
     fprintf(stderr, "Erreur de Malloc ! Impossible d'allouer de la mémoire.\n");
     exit(1);
  }

  memcpy(result, buffer->content + start_pos, length);
  result[length] = '\0';
  
  if (islocked) {
    buf_unlock(buffer);
  }
  return result;
}

char *lexer_getalphanum_rollback(buffer_t *buffer) {
    size_t start_pos = buffer->it;
    buf_lock(buffer);
    char *result = lexer_getalphanum(buffer);
    buf_rollback_and_unlock(buffer, buffer->it - start_pos);
    return result;
}


char *lexer_getop(buffer_t *buffer) {
    buf_skipblank(buffer);
    buf_lock(buffer);
    size_t start_pos = buffer->it;
    char first_char = buf_getchar(buffer);

    char second_char = buf_getchar(buffer);
    buf_rollback(buffer, 1);  // Always rollback the second character

    char *result = NULL;
    size_t length = 1;

    switch (first_char) {
        case '+':
        case '-':
            if (second_char == '+' || second_char == '-') {
                length = 2;
                buf_getchar(buffer);  // Consume the second character
            }
            break;
        case '=':
        case '<':
        case '>':
            if (second_char == '=') {
                length = 2;
                buf_getchar(buffer);  // Consume the second character
            }
            break;
        case '*':
        case '/':
            break;
        default:
            buf_rollback_and_unlock(buffer, buffer->it - start_pos);
            return NULL;
    }

    result = (char *)malloc(length + 1);  
    if (!result) {
        fprintf(stderr, "Erreur de malloc : impossible d'allouer la mémoire.\n");
        exit(1);
    }

    memcpy(result, buffer->content + start_pos, length);
    result[length] = '\0';

    buf_unlock(buffer);
    return result;
}


long lexer_getnumber(buffer_t *buffer) {
  char *alphanum = lexer_getalphanum(buffer);
  size_t length = strlen(alphanum);
  char *numberFound = (char *)malloc(length + 1);
  if (!numberFound) {
    fprintf(stderr, "Erreur de malloc : impossible d'allouer la mémoire.\n");
    exit(1);
  }

  size_t index = 0;
  for (size_t i = 0; i < length; i++) {
  if (isdigit(alphanum[i]) || (i == 0 && alphanum[i] == '-')) {
    numberFound[index++] = alphanum[i];
  } else {
    break; // Arrêter dès qu'on rencontre un caractère non numérique
    }
  }
  numberFound[index] = '\0';
  long numberResult = strtol(numberFound, NULL, 10);
  return numberResult;

  // Récupérer le resultat de getalphanum
  // Vérifier si le caractère est un nombre
      // Recommencer tant que c'est un nombre
  // Renvoyer le nombre trouvé
}
