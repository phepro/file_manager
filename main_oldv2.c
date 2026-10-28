#include <ncurses.h>

#include <dirent.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

char **files_in_dir;
int file_count = 0;

//this shit dont work

char path[100];
char empty_path[100];
char start_path[100];
char new_path[100];

void init_files (DIR *dir) {
    int i = 0;


    struct dirent *dir_entry;

    if (dir == NULL) {
        printf("Cant open dir: %s\n", path);
    }



    while ((dir_entry = readdir(dir)) != NULL) {
        //char current_file[15] = dir_entry->d_name;
        //files_in_dir[i] = current_file;
        //strcpy(files_in_dir[i], dir_entry->d_name);
        //i++;
        //
        file_count++;
    }
    closedir(dir);

    dir = opendir(path);
    files_in_dir = (char**)malloc(sizeof(char*)*file_count);
    while ((dir_entry = readdir(dir)) != NULL) {
        strcpy(files_in_dir[i], dir_entry->d_name);
        i++;
    }
    closedir(dir);
}

void print_files () {
    for (int i = 0; i < 15; i++) {
        printw("%d: %s \n", i+1, files_in_dir[i]);
    }
}

void print_current_dir () {
    char cwd[PATH_MAX];

    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        printw("Current dir.: %s\n", cwd);
    }

    else {
        printw("Current dir.: (getcwd failed)\n");
    }
}

void print_content_to_screen (char path[100];) {
    DIR *dir = opendir(path);

    print_current_dir();

    init_files(dir);
    print_files();
}

void path_up () {
    char path_temp[100];
    int x;

    for (int i = 99; i > -1; i--) {
        if (path[i] == '/') {
            x = i;
            break;
        }
    }

    //strcpy(path, empty_path);

    for (int i = 0; i < x; i++) {
        path_temp[i] = path[i];
    }

    strcpy(path, path_temp);
}

int main () {
    int ch;
    char cwd[PATH_MAX];

    if (strlen(path) == 0) {
        if (getcwd(cwd, sizeof(cwd)) != NULL) {
            strcpy(start_path, cwd);
            strcpy(path, start_path);
        }
    }
    else {
        strcpy(path, new_path);
    }

	initscr();			/* Start curses mode 		*/
	raw();				/* Line buffering disabled	*/
	keypad(stdscr, TRUE);		/* We get F1, F2 etc..		*/
	noecho();			/* Don't echo() while we do getch */

    while (true) {
        clear();

        print_content_to_screen();

        ch = getch();

        if (ch == KEY_F(1)) {
            break;
        }

        else if (ch == KEY_F(2)) {
            path_up();
        }

        refresh();
        getch();
    }

    endwin();

    return 0;
}
