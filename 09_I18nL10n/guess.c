#include <stdio.h>
#include <string.h>
#include <libintl.h>
#include <locale.h>
#include <stdlib.h>

#define _(STRING) gettext(STRING)

int main() {
    setlocale (LC_ALL, "");
    char *ss = bindtextdomain("guess", ".");
    textdomain("guess");

    char msg[10];
    int l = 1, r = 100, flag;
    printf(_("Come up with a number from %d to %d\n"), l, r);
    while(l < r) {
        int m = (int)((l + r) / 2);
        printf(_("Is this number greater than %d or not?\n"), m);
        scanf("%s", msg);
        if(strcmp("yes", msg) == 0) {
            l = m + 1;
        } else if(strcmp(msg, "no") == 0) {
            r = m;
        } else {
            printf(_("Incorrect value %s - type yes or no\n"), msg);
            continue;
        }
    }
    printf(_("Your number is %d\n"), l);

    return 0;
}
