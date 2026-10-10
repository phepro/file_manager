#include <stdio.h>
#include <dirent.h>
#include <ncurses.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

struct dirent *dir_entry;  // Pointer for directory entry

void print_to_tui_screen (DIR *dir);
void tui_current_dir_path_name ();

char current_key[10];

int ncurses_shit (DIR *dir) {

    initscr();
    cbreak();
    noecho();
    
    tui_current_dir_path_name();
    print_to_tui_screen(dir);

    refresh();
    getch();

    endwin();

    return 0;
}

void init_ncurses () {
    initscr();
    cbreak();
    noecho();
}

void init_window_contents (DIR *dir) {
    tui_current_dir_path_name();
    print_to_tui_screen(dir);

}

void window_loop (DIR *dir) {
    //WINDOW *main_window;

    while (true) {

        init_window_contents(dir);
        printw("Key pressed: %s\n", current_key);

        refresh();
        int ch = getch();

        if (ch == KEY_LEFT) {
            char key[] = "Key left"; 
            strcpy(current_key, key);
        }
        else if (ch == KEY_RIGHT) {
            exit(0);
        }
        else {
            char key[] = "None";
            strcpy(current_key, key);
        }

        ungetch(ch);
        sleep(2);
        
    }
}

void window (DIR *dir) {
    init_ncurses();
    window_loop(dir);
    endwin();
}

void tui_current_dir_path_name () {
    char cwd[PATH_MAX];

    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        printw("Cur. dir: %s\n", cwd);
    } else {
        printw("Cur. dir: (getcwd failed)\n");
    }
}

void print_to_tui_screen (DIR *dir) {
    // Refer https://pubs.opengroup.org/onlinepubs/7990989775/xsh/readdir.html
    // for readdir()
    while ((dir_entry = readdir(dir)) != NULL)
            printw("%s\n", dir_entry->d_name);

}

void close_dir(DIR *dir) {

    closedir(dir); 
}


int open_dir (char *dir_name, DIR *dir) {
    // opendir() returns a pointer of DIR type. 
    //DIR *dir = opendir(".");

    if (dir == NULL)  // opendir returns NULL if couldn't open directory
    {
        printf("Could not open current directory" );
        return 0;
    }
    
    // Refer https://pubs.opengroup.org/onlinepubs/7990989775/xsh/readdir.html
    // for readdir()
    //while ((dir_entry = readdir(dir)) != NULL)
    //      printf("%s\n", dir_entry->d_name);

    return 0;
}

/*
void print_dir () {
    // Refer https://pubs.opengroup.org/onlinepubs/7990989775/xsh/readdir.html
    // for readdir()
    while ((dir_entry = readdir(dir)) != NULL)
            printf("%s\n", dir_entry->d_name);

}
*/


char *arg_parser (int argc, char *argv[]) {
    if (argc > 1) {
        return argv[1];   
    }
    
    /*
    else {
        fputs("Not enough arguments!", stdout);
    }
    */

    return NULL;
}

int main (int argc, char *argv[]) {
    char *dir_name = arg_parser(argc, argv);
    
    DIR *dir = opendir(".");
;

    open_dir (dir_name, dir);
    //ncurses_shit(dir);
    window(dir);

    close_dir(dir);
    return 0;
}
