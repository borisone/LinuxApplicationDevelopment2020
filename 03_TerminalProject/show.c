#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define WIDTH 80
#define HEIGHT 30
#define STARTY 2
#define STARTX 5

const int MAXLEN = WIDTH;

void writeln(char *buffer, FILE *f, int *finish, int *skip_next_line, WINDOW *win, int *line_number) {
    if(fgets(buffer, MAXLEN, f) == NULL) {
        *finish = 1;
        return;
    }
    if(*skip_next_line) {
        *skip_next_line = 0;
        return;
    }
    wprintw(win, "%4d: %s", *line_number, buffer);
    if(strlen(buffer) == MAXLEN - 1 && buffer[MAXLEN - 1] != '\n') {
        *skip_next_line = 1;
    }
    (*line_number)++;
}

void show_content(char *filename) {
    FILE *f = fopen(filename, "r");

    if(f == NULL) {
        printf("Error opening file");
        exit(EXIT_FAILURE);
    }

    fseek(f, 0, SEEK_END);
    int filesize = ftell(f) + 1;
    fseek(f, 0, SEEK_SET);

    initscr();
    noecho();
    keypad(stdscr, TRUE);
    wrefresh(stdscr);
    printw("File: '%s', File Size: '%d' bytes\n", filename, filesize);

    WINDOW *border_win = newwin(HEIGHT+2, WIDTH+9, STARTY, STARTX);
    wborder(border_win, '|', '|', '-', '-', '+', '+', '+', '+');
    wrefresh(border_win);
    WINDOW *content_win = newwin(HEIGHT, WIDTH+5, STARTY+1, STARTX+2);
    scrollok(content_win, TRUE);
    refresh();

    int finish = 0, line_number = 1, skip_next_line = 0;
    char *buffer = (char *) malloc((MAXLEN + 1) * sizeof(char));
    for(int i = 0; i < HEIGHT; i++) {
         writeln(buffer, f, &finish, &skip_next_line, content_win, &line_number);
    }

    int c;
    while(!finish && (c = wgetch(content_win)) != 27) {
        if(c == ' ') {
             writeln(buffer, f, &finish, &skip_next_line, content_win, &line_number);
        }
    }

    refresh();
    endwin();
    fclose(f);
}

// --------------------------------------------- Long String Example ----------------------------------------------------------------------

int main(int argc, char **argv) {
    if(argc != 2) {
        printf("Invalid number of arguments\n");
        exit(EXIT_FAILURE);
    }
    show_content(argv[1]);
    return 0;
}
