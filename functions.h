//
// Created by jackt on 19/02/2026.
//

#ifndef JACKTEMPLE_PROJECT2_FUNCTIONS_H
#define JACKTEMPLE_PROJECT2_FUNCTIONS_H
#define MAX_LEN 200
#define TASK_WIDTH 12
#define MAX_TASKS 10
#define COL_WIDTH 6
#define DEP_WIDTH 13

//enum of months. We are using JAN = 0 for our array indexing.
//Makes program easier to read.
typedef enum {
    JAN, FEB, MAR, APR, MAY, JUN,
    JUL, AUG, SEP, OCT, NOV, DEC
} Month;

void print_sample();
void remove_newline(char *str);

typedef struct {
    char tasks[MAX_LEN];
    int dependencies[MAX_LEN];
    int depend_count;
    Month start_month;
    Month end_month;
} Table;

int input_tasks(Table tasks[]);
void create_sample(Table sample[]);
void print_create(int n_tasks, Table tasks[]);
int edit_tasks(int n, Table tasks[]);
int check_cycle(Table tasks[], int n_task, int visited[], int rec_stack[], int path[], int *path_index);
int has_circ_dependency(Table tasks[], int t_count);
void clear_screen();
void print_ascii();

#endif //JACKTEMPLE_PROJECT2_FUNCTIONS_H
