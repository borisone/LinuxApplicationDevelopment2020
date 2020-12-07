#include <ncurses.h>
#include "re.h"

#define DX 3
#define ONLELINE 3
#define MAXSTR 80

void main() {
    WINDOW *winA, *winB, *winO;
    char pattern[MAXSTR], subject[MAXSTR];
    int c = 0;
    int half;

    initscr();
    cbreak();
    printw("Input:");
    refresh();

    half = (COLS-2*DX)/2;
    winA = newwin(ONLELINE, half, DX, DX);
    winB = newwin(ONLELINE, half, DX, DX+half);
    winO = newwin(LINES-ONLELINE-DX*2, (COLS-2*DX), DX+ONLELINE, DX);
    keypad(winA, TRUE);
    keypad(winB, TRUE);
    scrollok (winO, TRUE);
    wmove(winO, 1, 0);
    do {
        werase(winA); 
        box(winA, 0, 0);
        mvwgetnstr(winA, 1, 1, pattern, MAXSTR);
        werase(winB); 
        box(winB, 0, 0);
        mvwgetnstr(winB, 1, 1, subject, MAXSTR);
        Compiled compiled = compile(pattern, subject);
        if(compiled.result) {
            wprintw(winO, "  Compilation Error: %s\n", compiled.msg);
            continue;
        }
        Matched matched = match(subject, &compiled);
        if(matched.result) {
            wprintw(winO, "  Matching Error: %s\n", matched.msg);
            continue;
        }
        int *occurences = find(&matched);
        for(int i = 0; i < matched.rc; i++) {
            wprintw(winO, "  %d: %.*s\n", occurences[2*i], occurences[2*i+1], subject + occurences[2*i]);
        }
        box(winO, 0, 0);
        wrefresh(winO);
    } while(*pattern);

    endwin();
}
