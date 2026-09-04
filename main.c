#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "functions.h"

int main()
{
    char sample_choice[MAX_LEN]; //first choice - sample print or create your own.
    char choose_action[MAX_LEN]; //second choice - edit the sample, test, exit program

    Table *current_table;       //Can point to either sample or tasks depending on which array is active
    Table sample[MAX_TASKS];    //The struct for printing the sample table
    Table tasks[MAX_TASKS];     //the struct for creating your own table
    int n_tasks = 0;            //keeps track of the number of tasks

    printf("Welcome to Gantt Generator!!\n");
    printf("Please enter your choice:\n"
           "Enter 'sample' if you wish to see a sample chart.\n"
           "Enter 'create' if you wish to create your own chart\n");

    fgets(sample_choice, MAX_LEN, stdin); //reads in the users choice.
    remove_newline(sample_choice);        //removes the newline character from the enter of the string

    if (strcmp(sample_choice, "sample") == 0)
    {
        create_sample(sample);  //creates the sample chart
        current_table = sample; //pointer now points to the sample array
        n_tasks = MAX_TASKS;
        clear_screen();         //clear the screen before printing.
        print_create(MAX_TASKS, sample); //prints out the sample chart
    }
    else
    {
        n_tasks = input_tasks(tasks); //prompts user to enter values to create their own chart
        current_table = tasks;        //pointer now points to the user created tasks
        clear_screen();
        print_create(n_tasks, tasks); //prints out the chart the user created
    }

    //Loop where the user chooses to edit, test, or exit the program.
    while(true) //loops until valid choice is made.
    {
    printf("If you wish to: \nEdit the Gantt, type \"edit\" \nRun a test, type \"test\" \nExit, type \"exit\" \nPrint ASCII art, type \"art\"\n");
    fgets(choose_action, MAX_LEN, stdin); //read in choice
    remove_newline(choose_action); //remove the newline character

    if(strcmp(choose_action, "edit") == 0)
    {
        if(edit_tasks(n_tasks, current_table))
        {
            clear_screen();
            print_create(n_tasks, current_table);
        }
        else
        {
            continue;
        }
    }
    else if(strcmp(choose_action, "test") == 0)
    {
        printf("Testing\n");
        if (has_circ_dependency(current_table, n_tasks)) //check circular dependencies
        {
            printf("ERROR: Circular dependency detected.\n");
            printf("Use 'edit' to change dependencies, then run 'test; again.\n\n");
        }
        else
        {
            printf("No circular dependencies detected.\n\n");
        }
    }
    else if(strcmp(choose_action, "exit") == 0)
    {
        break; //exit the loop
    }
    else if(strcmp(choose_action, "art") == 0)
    {
        print_ascii();
    }
    else
    {
        printf("Invalid choice. Try again.\n"); //loop repeats
    }
    }


    return 0;
}
