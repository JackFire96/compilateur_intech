#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include "lexer.h"

char *lexer_getalphanum(buffer_t *buffer) {
  buf_skipblank(buffer);
  buf_lock(buffer);
  size_t start_pos = buffer->it;  
  size_t length = 0;

  do {
    char c = buf_getchar(buffer);
    if (isalnum(c)) {
      length++;
    } else {
      buf_rollback(buffer, 1);
      break;
    }
  } while (!buf_eof(buffer));

  if (length == 0) {
    buf_rollback_and_unlock(buffer, buffer->it - start_pos);
    return NULL;
  }

  char *result = (char *)malloc(length + 1);
  if (!result) {
     buf_rollback_and_unlock(buffer, buffer->it - start_pos);
     return NULL;
  }

  memcpy(result, buffer->content + start_pos, length);
  result[length] = '\0';

  buf_unlock(buffer);
  return result;
}

char *lexer_getalphanum_rollback(buffer_t *buffer) {
    buf_lock(buffer);
    size_t start_pos = buffer->it;
    char *result = lexer_getalphanum(buffer);
    buf_rollback_and_unlock(buffer, buffer->it - start_pos);
    return result;
}

// char *lexer_getop(buffer_t *buffer) {
//     buf_lock(buffer);
//     size_t start_pos = buffer->it;
//     char c = buf_getchar(buffer);
//     char *op = NULL;

//     if (c == '+' || c == '-' || c == '*' || c == '/' || c == '=') {
//         op = (char *)malloc(2);
//         if (!op) {
//             buf_rollback_and_unlock(buffer, buffer->it - start_pos);
//             return NULL;
//         }
//         op[0] = c;
//         op[1] = '\0';
//     } else {
//         buf_rollback(buffer, 1);
//     }

//     if (!op) {
//         buf_rollback_and_unlock(buffer, buffer->it - start_pos);
//     } else {
//         buf_unlock(buffer);
//     }

//     return op;
// }

// long lexer_getnumber(buffer_t *buffer) {
//     buf_lock(buffer);
//     size_t start_pos = buffer->it;
//     size_t length = 0;
//     int negative = 0;

//     char c = buf_getchar(buffer);
//     if (c == '-') {
//         negative = 1;
//         length++;
//     } else {
//         buf_rollback(buffer, 1);
//     }

//     while (true) {
//         c = buf_getchar(buffer);
//         if (isdigit(c)) {
//             length++;
//         } else {
//             buf_rollback(buffer, 1);
//             break;
//         }
//     }

//     if (length == 0 || (length == 1 && negative)) {
//         buf_rollback_and_unlock(buffer, buffer->it - start_pos);
//         return 0;
//     }

//     char *num_str = (char *)malloc(length + 1);
//     if (!num_str) {
//         buf_rollback_and_unlock(buffer, buffer->it - start_pos);
//         return 0;
//     }

//     memcpy(num_str, buffer->content + start_pos, length);
//     num_str[length] = '\0';

//     char *endptr;
//     long result = strtol(num_str, &endptr, 10);
//     free(num_str);

//     buf_unlock(buffer);
//     return result;
// }
