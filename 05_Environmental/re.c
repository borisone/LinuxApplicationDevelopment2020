#include <stdio.h>
#include <string.h>
#include "re.h"
#include "config.h"

Compiled compile(PCRE2_SPTR pattern, PCRE2_SPTR subject) {
    pcre2_code *re;

    int errnum;

    Compiled compiled;

    PCRE2_SIZE erroffs, subject_length;

    subject_length = (PCRE2_SIZE)strlen((char *)subject);
#ifdef DISABLE_UTF
    re = pcre2_compile(pattern, PCRE2_ZERO_TERMINATED, 0, &errnum, &erroffs, NULL);
#else
    re = pcre2_compile(pattern, PCRE2_ZERO_TERMINATED, PCRE2_UCP, &errnum, &erroffs, NULL);
#endif
    if (re == NULL) {
        PCRE2_UCHAR buffer[256];
        pcre2_get_error_message(errnum, buffer, sizeof(buffer));
        compiled.re = re;
        sprintf(compiled.msg, "PCRE2 compilation failed at offset %d: %s\n", (int)erroffs, buffer);
        compiled.result = -1;
        return compiled;
    }

    compiled.re = re;
    compiled.result = 0;
    return compiled;
}

Matched match(PCRE2_SPTR subject, Compiled *compiled) {
    PCRE2_SIZE subject_length = (PCRE2_SIZE)strlen((char *)subject);

    int rc;

    Matched matched;

    pcre2_match_data *match_data = pcre2_match_data_create_from_pattern(compiled->re, NULL);

    rc = pcre2_match(compiled->re, subject, subject_length, 0, 0, match_data, NULL);

    if (rc < 0) {
        switch(rc) {
        case PCRE2_ERROR_NOMATCH:
            sprintf(matched.msg, "No match\n");
            break;
        default:
            sprintf(matched.msg, "Matching error %d\n", rc);
            break;
        }
        pcre2_match_data_free(match_data);   /* Release memory used for the match */
        pcre2_code_free(compiled->re);       /*   data and the compiled pattern. */
        matched.result = -1;
        matched.rc = rc;
        return matched;
    }
    matched.result = 0;
    matched.match_data = match_data;
    matched.rc = rc;
    matched.re = compiled->re;
    return matched;
}

int* find(Matched *matched) {
    PCRE2_SIZE *ovector = pcre2_get_ovector_pointer(matched->match_data);
    int *occurrences = (int *)malloc(sizeof(int) * 2 * matched->rc);

    for (int i = 0; i < matched->rc; i++) {
        occurrences[2*i] = ovector[2*i];
        occurrences[2*i+1] = (int)(ovector[2*i+1] - ovector[2*i]);
    }
    pcre2_match_data_free(matched->match_data);  /* Release the memory that was used */
    pcre2_code_free(matched->re);                /* for the match data and the pattern. */
    return occurrences;
}
