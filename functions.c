#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include "functions.h"
#include <time.h>

/*This function takes in a struct Table, and creates a sample table that we coded that
the user can ask to be printed out*/
void create_sample(Table sample[])
{
    //Uses enums to make it more readable
    //Task 1
    strcpy(sample[0].tasks, "Task_1"); //the name of the task is put into the tasks array in sample
    sample[0].start_month = JAN;         //the month that the tasks starts at
    sample[0].end_month = MAR;           //the month the task ends
    sample[0].depend_count = 0;        //how many dependencies the task has

    //Task 2
    strcpy(sample[1].tasks, "Task_2");
    sample[1].start_month = APR;
    sample[1].end_month = JUN;
    sample[1].depend_count = 1;
    sample[1].dependencies[0] = 0; // depends on Task 1

    //Task 3
    strcpy(sample[2].tasks, "Task_3");
    sample[2].start_month = JUL;
    sample[2].end_month = SEP;
    sample[2].depend_count = 2;
    sample[2].dependencies[0] = 0; // depends on Task 1
    sample[2].dependencies[1] = 1; // depends on Task 2

    //Task 4
    strcpy(sample[3].tasks, "Task_4");
    sample[3].start_month = MAR;
    sample[3].end_month = MAY;
    sample[3].depend_count = 0;

    //Task 5
    strcpy(sample[4].tasks, "Task_5");
    sample[4].start_month = JUN;
    sample[4].end_month = AUG;
    sample[4].depend_count = 1;
    sample[4].dependencies[0] = 3; // depends on Task 4

    //Task 6
    strcpy(sample[5].tasks, "Task_6");
    sample[5].start_month = JUL;
    sample[5].end_month = AUG;
    sample[5].depend_count = 2;
    sample[5].dependencies[0] = 3;  // depends on Task 4
    sample[5].dependencies[1] = 4;  // depends on Task 5

    //Task 7
    strcpy(sample[6].tasks, "Task_7");
    sample[6].start_month = AUG;
    sample[6].end_month = SEP;
    sample[6].depend_count = 0;

    //Task 8
    strcpy(sample[7].tasks, "Task_8");
    sample[7].start_month = AUG;
    sample[7].end_month = OCT;
    sample[7].depend_count = 1;
    sample[7].dependencies[0] = 5; // depends on Task 6

    //Task 9
    strcpy(sample[8].tasks, "Task_9");
    sample[8].start_month = SEP;
    sample[8].end_month = NOV;
    sample[8].depend_count = 0;

    //Task 10
    strcpy(sample[9].tasks, "Task_10");
    sample[9].start_month = NOV;
    sample[9].end_month = DEC;
    sample[9].depend_count = 2;
    sample[9].dependencies[0] = 7; //depends on Task 8
    sample[9].dependencies[1] = 8; //depends on Task 9
}

void print_sample() //creates and prints out a sample Gantt for the user
{
    Table sample[MAX_TASKS];

    create_sample(sample); //calls the create_sample function to create the sample with the tasks, months and dependencies we specified

    print_create(MAX_TASKS, sample); //calls the print function that will print out the formatted Gantt chart.
}

/*This function takes in a Table struct tasks and prompts the user to enter all values in order to create their own
Gantt chart. They enter then number of tasks, task names, start and end months and dependencies. It return the number of
tasks that the user adds*/
int input_tasks(Table tasks[]) {
    //using this buffer array and atoi, we don't use both scanf and fgets throughout the code, only fgets
    //this prevents us getting bugs later if the newline character is accidently left in somewhere
    char buffer[20]; //this stores the users input before it gets converted into an integer

    printf("How many tasks would you like to add? (1-10) \n");
    fgets(buffer, 20, stdin); //this prevents mixing scanf and fgets
    int n = atoi(buffer);         //this converts the number as a string into an integer
                                  //n = the number of tasks.
    for (int i = 0; i < n; i++)
    {
        printf("Please enter the task name: \n");
        fgets(tasks[i].tasks, MAX_LEN, stdin);      //reads the tasks in from the user
        remove_newline(tasks[i].tasks);             //removes any trailing newline character.

        tasks[i].tasks[TASK_WIDTH] = '\0';

        int start, end;

        while (1)
        {
            printf("Start month (1-12): \n");
            fgets(buffer, 20, stdin);
            start = atoi(buffer);

            if (start >= 1 && start <= 12)
            {
                break;
            }
            printf("Invalid month. Please enter a number between 1 and 12.\n");
        }
        tasks[i].start_month = (Month)(start - 1);   //converts user input (1–12) to 0–11 and casts it to the Month enum.

        while (1)
        {
            printf("End month (1-12): \n");
            fgets(buffer, 20, stdin);
            end = atoi(buffer);

            if (end < 1 || end > 12)
            {
                printf("Invalid month. Please enter a number between 1 and 12.\n");
                continue;
            }
            if (end < start)
            {
                printf("End month cannot be earlier than start month.\n");
                continue;
            }

            break;
        }
        tasks[i].end_month = (Month)(end - 1);     //does the same as above for the end month.

        printf("Enter the number of dependencies: \n");
        fgets(buffer, 20, stdin);
        tasks[i].depend_count = atoi(buffer);       //converts dependecie count input into an integer

        for(int j = 0; j < tasks[i].depend_count; j++)
        {
            printf("Enter dependenet task (1-%d): \n", n);
            fgets(buffer, 20, stdin);
            tasks[i].dependencies[j] = atoi(buffer) - 1;    //adds the dependencies as integers into the array, tracking the dependent tasks
        }
    }

    return n; //returns the number of tasks the user adds.
}

//This function takes in the number of tasks and Table struct tasks and prints out the Gantt chart.
void print_create(int n_tasks, Table tasks[])
{
    //Months array matches the Month enum by position
    const char *months[] = {
        "Jan","Feb","Mar","Apr","May","Jun",
        "Jul","Aug","Sep","Oct","Nov","Dec"
    };

    printf("%-*s|", TASK_WIDTH, "");    //prints the blank space before the first month to make room for the task name column on the right

    for (Month m = JAN; m <= DEC; m++) //loops through every month and prints them.
        printf("%-*s|", COL_WIDTH, months[m]);  //printing the month headers, formatted to COL_WIDTH size, with | between them

    printf("%-*s|\n", DEP_WIDTH, "Dependencies"); //prints the dependencies column at the end of all the months.

    for (int i = 0; i < n_tasks; i++)   //prints out all the tasks into the task column and prints # when then task is scheduled
    {
        printf("%-*s|", TASK_WIDTH, tasks[i].tasks);   //print the task name
        for (int j = 0; j < 12; j++)                    //go through the 12 months
        {
            if (j >= tasks[i].start_month && j <= tasks[i].end_month)    //checks if the current task is within the tasks duration
                printf("%-*s|", COL_WIDTH, "#####");  // if it is in the duration, print the in progress bar ######
            else
                printf("%-*s|", COL_WIDTH, "");       // if not print the cell empty
        }

        int printed = 0;    //counts the spaces in dependencies column to align border

        if(tasks[i].depend_count > 0) // check if there's any dependencies
        {
            for(int k = 0; k < tasks[i].depend_count; k++)
            {
                int dep = tasks[i].dependencies[k] + 1;
                printf("%d ", dep);    //if there are any dependencies, print the tasks the current task depends on

                if (dep >= 10)
                    printed += 3;   //'1','0','' = 3 characters
                else
                    printed+= 2;    //'2','' = 2 characters
            }
        }

        for(int s = printed; s < DEP_WIDTH; s++)    //prints the remaining spaces, column width - number of dependency numbers.
        {
            putchar(' ');
        }

        printf("|\n");
    }
}

//This taks in the number of tasks and the Table tasks and prompt the user to edit tasks in the sample table or their created table.
//and the editted chart is created
int edit_tasks(int n, Table tasks[])
{
    //stores the tasks the user wants to edit
    char buffer[20];
    printf("Which task would you like to edit? (1-%d): \n", n);   //asks the user which task within the current chart size they want to edit
    fgets(buffer, 20, stdin);
    int choice = atoi(buffer);  //converts the choice from char to integer
    choice--;  // converts to index

    if(choice < 0 || choice >= n)   //if the choice is not on the task table, print an error message
    {
        printf("Invalid task number\n");
        return 0;
    }

    printf("Enter new task name or current task name: \n");   //can change name or keep it the same.
    fgets(tasks[choice].tasks, MAX_LEN, stdin);
    remove_newline(tasks[choice].tasks);

    tasks[choice].tasks[TASK_WIDTH] = '\0';         //limits user entry to 12 letters

    int start, end;

    while (1)
        {
            printf("Start month (1-12): \n");
            fgets(buffer, 20, stdin);
            start = atoi(buffer);

            if (start >= 1 && start <= 12)
            {
                break;
            }
            printf("Invalid month. Please enter a number between 1 and 12.\n");
        }
        tasks[choice].start_month = (Month)(start - 1);   //converts user input (1–12) to 0–11 and casts it to the Month enum.

        while (1)
        {
            printf("End month (1-12): \n");
            fgets(buffer, 20, stdin);
            end = atoi(buffer);

            if (end < 1 || end > 12)
            {
                printf("Invalid month. Please enter a number between 1 and 12.\n");
                continue;
            }
            if (end < start)
            {
                printf("End month cannot be earlier than start month.\n");
                continue;
            }

            break;
        }
        tasks[choice].end_month = (Month)(end - 1);     //does the same as above for the end month.

    printf("Enter the number of dependencies: \n");
    fgets(buffer, 20, stdin);
    tasks[choice].depend_count = atoi(buffer);              //dependencies changed as ints

    for(int j = 0; j < tasks[choice].depend_count; j++)
    {
        printf("Enter dependent task (1-%d): \n", n);
        fgets(buffer, 20, stdin);
        tasks[choice].dependencies[j] = (atoi(buffer) - 1); //dependent tasks added
    }
    return 1;
}

/* This takes in the tasks in the table, the task that is to be tested, an array to mark what tasks have been
 * completely checked, an array to mark tasks currently in the recursion path, an array to store the current chain of tasks,
 * and a pointer to mark the current position in the path.
The function recursively goes through each dependency path to check if the chain leads back to a task that is already
in the current recursion stack. If this task is found, there is a circular dependency.
If a path reaches a task with no more dependencies, the function goes back and looks at  different dependency paths.
 */
int check_cycle(Table tasks[], int n_task, int visited[], int rec_stack[], int path[], int *path_index)
{
    visited[n_task] = 1; //marks task as visited, so it is not fully explored again
    rec_stack[n_task] = 1;  //set to 1 to flag it as in the current recursion chain

    //store the current task in the path so if a circular dependency is found, the chain can be printed
    path[*path_index] = n_task;
    (*path_index)++;

    //loop through all tasks this task depends on
    for (int i = 0; i < tasks[n_task].depend_count; i++)
    {
        int dep = tasks[n_task].dependencies[i];    //gets the dependency

        if (!visited[dep])  //if that task has not been visited yet, recursively explore it.
        {
            if (check_cycle(tasks, dep, visited, rec_stack, path, path_index))
                return 1;   //if the recursive call finds a cycle, return 1.
        }
        else if (rec_stack[dep])    //if that task is already in the recursion stack
        {
            //a circular dependency has been detected!!!!
            printf("Circular dependency detected:\n");

            int start = 0;
            //find where the cycle started in the path.
            for (int j = 0; j < *path_index; j++)
            {
                if (path[j] == dep)
                {
                    start = j;
                    break;
                }
            }

            //print from that start point onwards
            for (int j = start; j < *path_index; j++)
            {
                printf("%d ->", path[j] + 1);
            }
            printf("%d\n", dep + 1);

            return 1;
        }

    }

    //when a task has been explored, remove if from the recursion stack and the current path.
    rec_stack[n_task] = 0;
    (*path_index)--;

    return 0; //return 0, no cycle has been detected
}

int has_circ_dependency(Table tasks[], int t_count)
{
    //tracking arrays
    int visited[MAX_TASKS] = {0};
    int rec_stack[MAX_TASKS] = {0};
    int path[MAX_TASKS] = {0};
    int path_index = 0;

    //check every task
    for (int i = 0; i < t_count; i++)
    {
        if (!visited[i])
        {
            //if a cycle is found, stop.
            if (check_cycle(tasks, i, visited, rec_stack, path, &path_index))
                return 1;
        }
    }

    //if nothing found, return 0;
    return 0;
}

void remove_newline(char *str)
/*This take a pointer to a string, in my case the string of an artists name or song name and removes the new line character.
 * This is so that I can check if a string is empty if the ENTER key is pressed and the program can move to the next action.
 */
{
    int i = 0;
    while (str[i] != '\0') {    //for every character before the null terminator, which ends a string,
        if (str[i] == '\n') {   //if a character is the newline character '\n'.
            str[i] = '\0';      //replace the newline character with the null terminator to end the string in this position instead
            break;              //exit the loop
        }
        i++;                    //move to next character
    }
}

void clear_screen()
//This function clears the screen before printing a new chart.
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void print_ascii()
{
printf(".................;S?*.:;,.................................................................\n");
printf("................,;;;;:*:,.................................................................\n");
printf("..............,;;++;:;;?+:................................................................\n");
printf(".............:;:,:+;:;::+?*:..............................................................\n");
printf("...........,+;:;;;;;**;:::;**+,...........................................................\n");
printf("...........;+++;:::,,+;+:;;::+?+:.........................................................\n");
printf("...........:::,.......;;;,:;+:;+**+,......................................................\n");
printf(".......................;+*:::::::++**++:,.................................................\n");
printf("........................:*:+;;,::::::;++??*++:............................................\n");
printf(".........................,+*;,;:::,,:;;:,;::;+:,..........................................\n");
printf("...........................:+;+:+;,;:,:,:::,::,:::,.......................................\n");
printf("............................,;;:;+;,;:,,::::,:,,::,::::,,::,..............................\n");
printf("..............................,;++:,,::,:;:,:,:::,,::,,,,,,,::,,..........................\n");
printf("................................:*,::+::+;,;:,,,,,,:,,.,,,:,,,,::,........................\n");
printf("................................;:,,:::::,,,:;:,::,::::,;:,,::,::,:.......................\n");
printf("................................+,:,:,:,;,*,:;,::,,,,;;,,:::,:,:,;;;......................\n");
printf("................................;+::+,;;,,?:+:::;,;+,::+,::,;::;;:+;:.....................\n");
printf(".................................;;;:;:,:,+,**,;;,::,;;?;,::,+::::;;:.....................\n");
printf("..................................:?::,::*?:;::+;;;*:;++*:::::;:;::::.....................\n");
printf("...................................;:;:;;??+++:+++:;+*+?#*;:::;::;,::.....................\n");
printf("...................................:::,++++..,;;;;;;:,.:+**;::;::;.;:.....................\n");
printf("...................................::,;;+:;..............;;:+::::;,,S:....................\n");
printf("...................................::::*:,+...............;,:+;:::;,?#....................\n");
printf("...................................;,;;*:,;,..............,;::+;:::+;S,...................\n");
printf("...................................;,:+,;,,;...............;,:*+:,,*,?,...................\n");
printf("..................................::,,;.;,,;...............:,;+,;;:+.+....................\n");
printf("..................................:;;;...;,;...............;,,;.,;:+.*;...................\n");
printf("..................................;,;....,:::..............;,::..+,+.,,...................\n");
printf(".................................::::.....;,;..............;,;,..;,;:.....................\n");
printf(".................................;,;......;,;,............,;:+...::,;.....................\n");
printf("................................;:::......::,;............;::;...,:,+.....................\n");
printf("...............................::;;......,:,+,..........,:;;;,...::+;.....................\n");
printf(".............................,*??;......,??*;..........:???;....;*++......................\n");
}