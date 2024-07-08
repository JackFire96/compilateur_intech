#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "lexer.h"
#include "buffer.h"

FILE *fmemopen(void *buf, size_t size, const char *mode) {
    FILE *f = tmpfile();
    if (f == NULL) return NULL;
    fwrite(buf, 1, size, f);
    rewind(f);
    return f;
}

void test_lexer_getalphanum() {
    char data[] = "abc123";
    FILE *f = fmemopen(data, strlen(data), "r");
    buffer_t buffer;
    buf_init(&buffer, f);
    char *result = lexer_getalphanum(&buffer);
    assert(strcmp(result, "abc123") == 0);
    free(result);
    fclose(f);
}

void test_lexer_getalphanum_rollback() {
    char data[] = "abc123";
    FILE *f = fmemopen(data, strlen(data), "r");
    buffer_t buffer;
    buf_init(&buffer, f);
    char *result = lexer_getalphanum_rollback(&buffer);
    assert(strcmp(result, "abc123") == 0);
    free(result);
    fclose(f);
}

void test_lexer_getop() {
    char data[] = "+-*/";
    FILE *f = fmemopen(data, strlen(data), "r");
    buffer_t buffer;
    buf_init(&buffer, f);
    char *result = lexer_getop(&buffer);
    assert(strcmp(result, "+") == 0);
    free(result);
    result = lexer_getop(&buffer);
    assert(strcmp(result, "-") == 0);
    free(result);
    fclose(f);
}

void test_lexer_getnumber() {
    char data[] = "-12345";
    FILE *f = fmemopen(data, strlen(data), "r");
    buffer_t buffer;
    buf_init(&buffer, f);
    long result = lexer_getnumber(&buffer);
    assert(result == -12345);
    fclose(f);
}

int main() {
    test_lexer_getalphanum();
    test_lexer_getalphanum_rollback();
    test_lexer_getop();
    test_lexer_getnumber();
    printf("All tests passed.\n");
    return 0;
}
