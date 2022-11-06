#include <stdio.h>

void create_poll();
void poll_list();

int admin_screen()
{
    int option;
    printf("Please select one of this option\n");
    printf("1) Create new poll\n");
    printf("2) View poll report\n");

    printf("Enter your option: ");
    scanf("%d", &option);

    if (option == 1)
    {
        create_poll();
    }
    else if (option == 2)
    {
        poll_list();
    }

    return 0;
}

void create_poll()
{
    FILE *poll_list;
    FILE *poll_choice;

    char name[100];
    char choice[100];
    int choice_num;

    printf("Enter name: ");
    scanf("%s", name);

    poll_list = fopen("poll_list.txt", "a+");

    fputs(name, poll_list);
    fputs("\n", poll_list);

    poll_choice = fopen(strcat(name, ".txt"), "a+");

    printf("How many choice your want: ");
    scanf("%d", &choice_num);

    for (int i = 0; i < choice_num; i++)
    {
        printf("Enter %d choice: ", i);
        scanf("%s", choice);
        fputs(strcat(choice, " 0"), poll_choice);
        fputs("\n", poll_choice);
    }

    fclose(poll_list);
    fclose(poll_choice);
}

void poll_list()
{
    FILE *poll_list;
    FILE *choice_list;

    poll_list = fopen("poll_list.txt", "r");

    char poll[100];
    char choice[100];

    int number = 1;
    int poll_number;

    while (fgets(poll, 100, poll_list))
    {
        printf("%d) %s", number, poll);
        number++;
    }

    number = 1;

    printf("Enter number : ");
    scanf("%d", &poll_number);

    for (int i = 0; i < poll_number - 1; i++)
    {
        fgets(poll, 100, poll_list);
    }

    poll[strlen(poll) - 1] = '\0';

    choice_list = fopen(strcat(poll, ".txt"), "r");

    while (fgets(choice, 100, choice_list))
    {
        printf("%d) %s", number, choice);
        number++;
    }

    fclose(poll_list);
}