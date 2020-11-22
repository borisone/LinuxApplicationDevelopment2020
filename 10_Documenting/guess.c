/** @file */ 
#include <stdio.h>
#include <string.h>
#include <libintl.h>
#include <locale.h>
#include <stdlib.h>
#include "config.h"

#define _(STRING) gettext(STRING)

#define HELP _("\
`guess' is able guess the number you thought about.\n\
\n\
Usage: ./guess [OPTION]...\n\
\n\
Defaults for the options are specified in brackets.\n\
\n\
Configuration:\n\
  --help                  display this help and exit\n\
  --version               display version information and exit\n\
  -r                      enable roman mode\n")

/** \brief Mapping from Arabic to Roman numbers*/
static char* ARABIC2ROMAN[100] = {"I", "II", "III", "IV", "V", "VI", "VII", "VIII", "IX", "X", "XI", "XII", "XIII", "XIV", "XV", "XVI", "XVII", "XVIII", "XIX", "XX", "XXI", "XXII", "XXIII", "XXIV", "XXV", "XXVI", "XXVII", "XXVIII", "XXIX", "XXX", "XXXI", "XXXII", "XXXIII", "XXXIV", "XXXV", "XXXVI", "XXXVII", "XXXVIII", "XXXIX", "XL", "XLI", "XLII", "XLIII", "XLIV", "XLV", "XLVI", "XLVII", "XLVIII", "XLIX", "L", "LI", "LII", "LIII", "LIV", "LV", "LVI", "LVII", "LVIII", "LIX", "LX", "LXI", "LXII", "LXIII", "LXIV", "LXV", "LXVI", "LXVII", "LXVIII", "LXIX", "LXX", "LXXI", "LXXII", "LXXIII", "LXXIV", "LXXV", "LXXVI", "LXXVII", "LXXVIII", "LXXIX", "LXXX", "LXXXI", "LXXXII", "LXXXIII", "LXXXIV", "LXXXV", "LXXXVI", "LXXXVII", "LXXXVIII", "LXXXIX", "XC", "XCI", "XCII", "XCIII", "XCIV", "XCV", "XCVI", "XCVII", "XCVIII", "XCIX", "C"};

/**
 * Convert @p arabic from Arabic to Roman number.
 *
 * @param arabic An Arabic number, must be in range from 1 to 100.
 *
 * @returns @p arabic converted to the Roman number.
 */
char* arabic2roman(int arabic) {
    if(arabic <= 0 || arabic > 100) {
        printf(_("Arabic number must be in range from 1 to 100\n"));
        exit(1);
    }
    return ARABIC2ROMAN[arabic-1];
}

/**
 * Convert @p roman number from Roman to Arabic number
 *
 * @param roman A Roman number, must be in range from I to C.
 *
 * @returns @p roman converted to the Arabic number.
 */
int roman2arabic(char* roman) {
    for(int i = 1; i <= 100; i++) {
        if(strcmp(roman, ARABIC2ROMAN[i-1]) == 0)
            return i;
    }
    printf(_("Roman number must be in range from 1 to 100\n"));
    exit(1);
}

char* num2string(int ar, char *ro, int arabic_mode) {
    if(arabic_mode) {
        char *buf = (char *)malloc(sizeof(char) * 4); 
        sprintf(buf, "%d", ar);
        return buf;
    }
    return ro;
}

int main(int argc, char **argv) {
    setlocale (LC_ALL, "");
    char *ss = bindtextdomain("guess", ".");
    textdomain("guess");
    int arabic_mode = 1;
    if(argc > 1 && strcmp(argv[1], "--help") == 0) {
        return !printf("%s\n", HELP);
    } else if(argc > 1 && strcmp(argv[1], "--version") == 0) {
        return !printf(_("guess version: %s\n"), VERSION);
    }
    
    if(argc > 1 && strcmp(argv[1], "-r") == 0) {
        arabic_mode = 0;
    }

    char msg[10];
    int l = 1, r = 100;
    printf(_("Come up with a number from %s to %s\n"), num2string(l, arabic2roman(l), arabic_mode), num2string(r, arabic2roman(r), arabic_mode));
    while(l < r) {
        int m = (int)((l + r) / 2);
        printf(_("Is this number greater than %s or not?\n"), num2string(m, arabic2roman(m), arabic_mode));
        scanf("%s", msg);
        if(strcmp("yes", msg) == 0 || strcmp("y", msg) == 0) {
            l = m + 1;
        } else if(strcmp(msg, "no") == 0 || strcmp("n", msg) == 0) {
            r = m;
        } else {
            printf(_("Incorrect value %s - type yes (y) or no (n)\n"), msg);
            continue;
        }
    }
    printf(_("Your number is %s\n"), num2string(l, arabic2roman(l), arabic_mode));

    return 0;
}
