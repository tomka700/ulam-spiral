#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

void program(int*** m, int* n, char* d, char (*r)[4]);
// tasks
int menu();
void guide();
int** gen_m(int** m, int* n, char* d, char (*r)[4]);
void print_m(int** m, int n);
void save_m(int** m, int n, char d, char r[4]);
int** load_m(int** m, int* n);
// helpers
void enter();
void p_enter();
void free_m(int** m, int n);
// init while main
int main() {
    int** m = NULL;
    int n = 0;
    char d = '-';
    char r[4] = "ERR";

    while (1) {
        program(&m, &n, &d, &r);
    }
}
// main
void program(int*** m, int* n, char* d, char (*r)[4]) {
    int choice = menu();
    switch (choice) {
        case 1:
            guide();
            break;
        case 2:
            free_m(*m, *n);
            *m = gen_m(*m, n, d, r);
            break;
        case 3:
            print_m(*m, *n);
            break;
        case 4:
            save_m(*m, *n, *d, *r);
            break;
        case 5:
            *m = load_m(*m, n);
            break;
        case 6:
            free_m(*m, *n);
            exit(0);
    }
}
//menu
int menu() {
    printf("\n");
    printf("o~~~~~~~~~~~~~~~o\n");
    printf("[ P R O G R A M ]\n");
    printf("]   S P I R A L [\n");
    printf("[ X I R T A M   ]\n");
    printf("o~~~~~~~~~~~~~~~o\n");
    printf("\n");
    printf("1 ~ Guide\n");
    printf("2 ~ Generate\n");
    printf("3 ~ Print\n");
    printf("4 ~ Save\n");
    printf("5 ~ Load\n");
    printf("6 ~ Exit\n");

    int out; 
    do {
        out = 0;
        printf("\nMenu: ");
        scanf("%d", &out);
        enter();
        if (out < 1 || out > 6) {
            printf("\nChoice must be between 1 and 6.\n");
        }
    } while (out < 1 || out > 6);

    return out;
}
// guide
void guide() {
    printf("\n");
    printf("o~~~~~Guide~~~~~o\n");
    printf("This program can be used to\n");
    printf("2 ~ Generate\n");
    printf("3 ~ Print\n");
    printf("4 ~ Save\n");
    printf("5 ~ Load\n");
    printf("spiral matrices.\n");
    p_enter();

    printf("Inside the main menu:\n");
    printf("The user must input a number between 1 and 6 and then press enter.\n");
    p_enter();

    printf("When generating:\n");
    printf("The matrix has to be square and its size must be between 1 and 20.\n");
    printf("The starting direction of the spiral is left, right, up or down (l/r/u/d).\n");
    printf("The direction of rotation is either clockwise or counterclockwise (cw/ccw).\n");
    p_enter();

    printf("When printing:\n");
    printf("The program will print the currently loaded matrix if it exists, otherwise it will return back to the main menu.\n");
    p_enter();

    printf("When saving:\n");
    printf("The program will save the currently loaded matrix into a file with a name of this format:\n");
    printf("spiral<size><starting direction><direction of rotation>.txt\n");
    printf("If there is no loaded matrix, the program will return back to the main menu.\n");
    p_enter();

    printf("When loading:\n");
    printf("The program will prompt the user to enter the name of a file.\n");
    printf("If the file exists, the program will load the matrix from the file.\n");
    printf("Otherwise, the program will return back to the main menu.\n");
    p_enter();

    printf("Example use case:\n");
    printf("Menu: 2\n");
    printf("Size: 3, Starting direction: l, Direction of rotation: cw\n");
    printf("Menu: 3\n");
    printf("3 4 5\n");
    printf("2 1 6\n");
    printf("9 8 7\n");
    printf("Menu: 4\n");
    printf("Menu: 6\n");
    p_enter();
}
// generate matrix
int** gen_m(int** m, int* n, char* d, char (*r)[4]) {
    printf("\n");
    printf("o~~~~~~~~Generate~~~~~~~~o\n");

    char conf;
    do {
        printf("\n");
        printf("Size: 0 < N < 21\n");
        printf("Starting direction: l / r / u / d\n");
        printf("Direction of rotation: cw / ccw\n");
        // reset vars
        *n = 0;
        *d = '-';
        strcpy(*r, "ERR");
        // size n
        do {
            printf("\nSize: ");
            scanf("%d", n);
            enter();
            if (*n < 1 || *n > 20) {
                printf("\nSize must be between 1 and 20.\n");
            }
        } while (*n < 1 || *n > 20);
        // direction d
        do {
            printf("\nStarting direction: ");
            scanf("%c", d);
            enter();
            if (*d != 'l' && *d != 'r' && *d != 'u' && *d != 'd') {
                printf("\nDirection must be l, r, u or d.\n");
            }
        } while (*d != 'l' && *d != 'r' && *d != 'u' && *d != 'd');
        // rotation r
        do {
            printf("\nDirection of rotation: ");
            scanf("%s", r);
            enter();
            if (strcmp(*r, "cw") && strcmp(*r, "ccw")) {
                printf("\nDirection of rotation must be cw or ccw.\n");
            }
        } while (strcmp(*r, "cw") && strcmp(*r, "ccw"));
        // list choices
        printf("\n");
        printf("%d, %c, %s\n", *n, *d, *r);
        // confirm or reenter
        do {
            printf("\nConfirm? (y/n): ");
            scanf("%c", &conf);
            enter();
        } while (conf != 'y' && conf != 'n');
    } while (conf != 'y');
    // malloc matrix
    m = (int**)malloc(*n * sizeof(int*));
    for (int i = 0; i < *n; i++) {
        m[i] = (int*)malloc(*n * sizeof(int));
    }
    // init matrix
    for (int i = 0; i < *n; i++) {
        for (int j = 0; j < *n; j++) {
            m[i][j] = 0;
        }
    }
    // iter start pos
    int i = *n / 2;
    int j = *n / 2;
    int cw = strcmp(*r, "cw");
    if (*n % 2 == 0) {
        switch (*d) {
            case 'l':
                i = cw ? i - 1 : i;
                break;
            case 'u':
                j = cw ? j : j - 1;
                break;
            case 'r':
                i = cw ? i : i - 1;
                j--;
                break;
            case 'd':
                i--;
                j = cw ? j - 1 : j;
                break;
        }
    }
    // fill matrix from 1 to n ^ 2
    int num = 1;
    char tmp = *d;
    int turn = 2;
    while (num < pow(*n, 2) + 1) {
        m[i][j] = num;
        num++;
        // turn corners
        if (num - 1 == ceil((pow(turn, 2) + 3) / 4)) {
                switch (tmp) {
                    case 'l':
                        tmp = cw ? 'd' : 'u';
                        break;
                    case 'u':
                        tmp = cw ? 'l' : 'r';
                        break;
                    case 'r':
                        tmp = cw ? 'u' : 'd';
                        break;
                    case 'd':
                        tmp = cw ? 'r' : 'l';
                        break;
                }
            turn++;
        }
        // move pos
        switch (tmp) {
            case 'l':
                j--;
                break;
            case 'u':
                i--;
                break;
            case 'r':
                j++;
                break;
            case 'd':
                i++;
                break;
        }
    }
    return m;
}
// print matrix
void print_m(int** m, int n) {
    if (m == NULL) {
        printf("The matrix is in another castle.\n");
        p_enter();
        return;
    }

    printf("\n");
    printf("o~~~~~~~~Print~~~~~~~~o\n");
    // # of digits of max val - # of digits of current val
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            int sp = floor(log10(pow(n, 2))) - floor(log10(m[i][j]));
            for (int k = 0; k < sp; k++) {
                printf(" ");
            }
            printf("%d ", m[i][j]);
        }
        printf("\n");
    }
    p_enter();
}
// save matrix
void save_m(int** m, int n, char d, char r[4]) {
    if (m == NULL) {
        printf("The matrix is in another castle.\n");
        p_enter();
        return;
    }

    printf("\n");
    printf("o~~~~~~~~Save~~~~~~~~o\n");
    // 6 + 2 + 1 + 3 + (1 \0 ?) = 17
    char name[17];
    sprintf(name, "spiral%d%c%s.txt", n, d, r);
    FILE* file = fopen(name, "w");
    // write matrix to file
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            fprintf(file, "%d ", m[i][j]);
        }
        fprintf(file, "\n");
    }
    fclose(file);
    printf("Done.\n");
    p_enter();
}
// load matrix from file
int** load_m(int** m, int* n) {
    printf("\n");
    printf("o~~~~~~~~Load~~~~~~~~o\n");
    // comedy
    char fname[69];
    printf("File: ");
    scanf("%s", fname); 

    FILE* file = fopen(fname, "r");
    // check if file exists
    if (file == NULL) {
        printf("The file is in another castle.\n");
        p_enter();
        getchar(); // p_enter() breaks here
        return m;
    }
    // free after file check
    free_m(m, *n);
    // get # of rows
    *n = 0;
    char c;
    while ((c = fgetc(file)) != EOF && c != '\n') {
        if (c == ' ') {
            (*n)++;
        }
    }
    // rewind to start
    rewind(file);
    // malloc matrix
    m = (int**)malloc(*n * sizeof(int*));
    for (int i = 0; i < *n; i++) {
        m[i] = (int*)malloc(*n * sizeof(int));
    }
    // read matrix to memory
    for (int i = 0; i < *n; i++) {
        for (int j = 0; j < *n; j++) {
            fscanf(file, "%d", &m[i][j]);
        }
    }

    fclose(file);
    printf("Done.\n");
    p_enter();
    getchar(); // p_enter() breaks here
    return m;
}
// end of input do while
void enter() {
    char c;
    while ((c = getchar()) != EOF && c != '\n');
}
// QOL
void p_enter() {
    printf("Press enter to continue.\n");
    enter();
}
// free matrix from memory
void free_m(int** m, int n) {
    if (m != NULL) {
        for (int i = 0; i < n; i++) {
            free(m[i]);
        }
        free(m);
    }
}
