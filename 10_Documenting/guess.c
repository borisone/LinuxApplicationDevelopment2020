#include <stdio.h>
#include <string.h>
#include <libintl.h>
#include <locale.h>
#include <stdlib.h>

#define _(STRING) gettext(STRING)

char** ARABIC2ROMAN = {"I", "II", "III", "IV", "V", "VI", "VII", "VIII", "IX", "X", "XI", "XII", "XIII", "XIV", "XV", "XVI", "XVII", "XVIII", "XIX", "XX", "XXI", "XXII", "XXIII", "XXIV", "XXV", "XXVI", "XXVII", "XXVIII", "XXIX", "XXX", "XXXI", "XXXII", "XXXIII", "XXXIV", "XXXV", "XXXVI", "XXXVII", "XXXVIII", "XXXIX", "XL", "XLI", "XLII", "XLIII", "XLIV", "XLV", "XLVI", "XLVII", "XLVIII", "XLIX", "L", "LI", "LII", "LIII", "LIV", "LV", "LVI", "LVII", "LVIII", "LIX", "LX", "LXI", "LXII", "LXIII", "LXIV", "LXV", "LXVI", "LXVII", "LXVIII", "LXIX", "LXX", "LXXI", "LXXII", "LXXIII", "LXXIV", "LXXV", "LXXVI", "LXXVII", "LXXVIII", "LXXIX", "LXXX", "LXXXI", "LXXXII", "LXXXIII", "LXXXIV", "LXXXV", "LXXXVI", "LXXXVII", "LXXXVIII", "LXXXIX", "XC", "XCI", "XCII", "XCIII", "XCIV", "XCV", "XCVI", "XCVII", "XCVIII", "XCIX", "C"};

char* arabic2roman(int arabic) {
    if(arabic <= 0 || arabic > 100) {
        printf("Arabic number must be in range from 1 to 100\n");
        exit(1);
    }
    return ARABIC2ROMAN[arabic];
}

int roman2arabic(char* roman) {
    for(int i = 1; i <= 100; i++) {
        if(strcmp(roman, ARABIC2ROMAN[i]) == 0)
            return i;
    }
    printf("Roman number must be in range from 1 to 100\n");
    exit(1);
}

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
            flag = 0;
        } else if(strcmp(msg, "no") == 0) {
            flag = 1;
        } else {
            printf(_("Incorrect value %s - type yes or no\n"), msg);
            continue;
        }
        if(flag) {
            l = m + 1;
        } else {
            r = m;
        }
    }
    printf(_("Your number is %d\n"), l);

    return 0;
}
