#include <stdio.h>
#include <string.h>
#include <time.h>

#define MAX_CATEGORIES 10
#define MAX_NAME_LENGTH 50

/* DEFINE 'CATEGORY' to include the name of the category, an indication of whether the timers running in the selected category as well as variables to store times */
struct category
{
    char name[MAX_NAME_LENGTH];
    int running;
    time_t start_time;
    time_t total_time;
};

/* SEARCH CATEGORIES */
int find_category(struct category categories[], char name[])
{
    for (int i = 0; i < MAX_CATEGORIES; i++)
    {
        if (strcmp(categories[i].name, name) == 0)
        {
            return i;
        }
    }
    return -1;
}
/* Start timer after making sure the selected category already exists, if not a new one will be created if MAX_CATEGORIES isn't reached yet */
void start_category(struct category categories[], char name[])
{
    int index = find_category(categories, name);
    if (index == -1)
    {
        for (int i = 0; i < MAX_CATEGORIES; i++)
        {
            if (categories[i].name[0] == '\0')
            {
                index = i;
                strcpy(categories[i].name, name);
                break;
            }
        }
    }
    if (index != -1)
    {
        categories[index].running = 1;
        categories[index].start_time = time(NULL);
    }
}

/* Stop function, will probably not use in favor of pause function, but could be useful in some applications so I'm including it as an option */
/* will verify category exists before trying to stop time, then saves the total elapsed time */
void stop_category(struct category categories[], char name[])
{
    int index = find_category(categories, name);
    if (index != -1 && categories[index].running)
    {
        time_t end_time = time(NULL); /* Grabs the current time as the stop time, will subtract the start time from it to get total time */
        categories[index].total_time += end_time - categories[index].start_time;
        categories[index].running = 0;
    }
}

void pause_category(struct category categories[], char name[])
{
    int index = find_category(categories, name);
    if (index != -1 && categories[index].running)
    {
        time_t pause_time = time(NULL);
        categories[index].total_time += pause_time - categories[index].start_time;
        categories[index].running = 0;
    }
}

void resume_category(struct category categories[], char name[])
{
    int index = find_category(categories, name);
    if (index != -1 && !categories[index].running)
    {
        categories[index].running = 1;
        categories[index].start_time = time(NULL);
    }
}

void reset_category(struct category categories[], char name[])
{
    int index = find_category(categories, name);
    if (index != -1)
    {
        categories[index].total_time = 0;
        categories[index].running = 0;
    }
}

void print_categories(struct category categories[])
{
    printf("Categories:\n");
    for (int i = 0; i < MAX_CATEGORIES; i++)
    {
        if (categories[i].name[0] != '\0')
        {
            printf("%s: %ld seconds\n", categories[i].name, categories[i].total_time);
        }
    }
}

void get_category(char *name)
{
    printf("Enter Category Name: ");
    scanf("%s", name);
}

int main()
{
    struct category categories[MAX_CATEGORIES] = {0};
    char command[MAX_NAME_LENGTH];
    char name[MAX_NAME_LENGTH];
    while (1) /* 'while (1)' creates an infinite loop to continue checking */
    {
        printf("Enter command (start, stop, pause, resume, reset, print, quit): ");
        scanf("%s", command);
        if (strcmp(command, "start") == 0) /* asks if given strings match or not, 0 indicates a match */
        {
            get_category(name);
            start_category(categories, name);
        }
        else if (strcmp(command, "stop") == 0)
        {
            get_category(name);
            stop_category(categories, name);
        }
        else if (strcmp(command, "pause") == 0)
        {
            get_category(name);
            pause_category(categories, name);
        }
        else if (strcmp(command, "resume") == 0)
        {
            get_category(name);
            resume_category(categories, name);
        }
        else if (strcmp(command, "reset") == 0)
        {
            get_category(name);
            reset_category(categories, name);
        }
        else if (strcmp(command, "print") == 0)
        {
            print_categories(categories);
        }
        else if (strcmp(command, "quit") == 0)
        {
            break;
        }
        else
        {
            printf("INVALID COMMAND\n");
        }
    }
    return 0;
}