#ifndef PCRE2_CODE_UNIT_WIDTH
#define PCRE2_CODE_UNIT_WIDTH 8
#endif

#include <pcre2.h>

typedef struct Compiled {
    int result;
    char msg[256];
    pcre2_code *re;
} Compiled;

typedef struct Matched {
    int result, rc;
    char msg[256];
    pcre2_code *re;
    pcre2_match_data *match_data;
} Matched;

int* find(Matched *matched);
Compiled compile(PCRE2_SPTR pattern, PCRE2_SPTR subject);
Matched match(PCRE2_SPTR subject, Compiled *compiled);

