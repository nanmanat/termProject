#include <stdio.h>
#include <math.h>
#include <string.h>

void create_poll();
void poll_list();
int percentage(int *percent, int size);

int admin_screen()
{
    int option;
    printf("\n\nPlease select one of this option\n");
    printf("1) Create new poll\n");
    printf("2) View poll list\n");
    printf("3) Quit\n\n");

    do
    {
        printf("Enter your option: ");
        scanf("%d", &option);
    } while (option < 1 || option > 3);

    if (option == 1)
    {
        create_poll();
    }
    else if (option == 2)
    {
        poll_list();
    }
    else if (option == 3)
    {
        return 0;
    }

    return 0;
}

void create_poll()
{
    FILE *poll_list;
    FILE *poll_choice;
    FILE *user_list;
    FILE *user_profile;

    char name[100];
    char choice[100];
    int choice_num;

    printf("\n\nEnter name: ");
    scanf("%s", name);

    poll_list = fopen("poll_list.txt", "a+");
    user_list = fopen("user.txt", "r");

    char role;
    char user[100];

    while (fgets(user, 100, user_list))
    {
        for (int i = 0; i < 100; i++)
        {
            if(user[i] == ' ')
            {
                user[i] = '\0';
                role = user[i + 1];
            }
        }
        if (role == '0')
        {
            user_profile = fopen(strcat(user, ".txt"), "a");

            fprintf(user_profile, "0\n");
        }
        
    }

    fputs(name, poll_list);
    fputs("\n", poll_list);

    poll_choice = fopen(strcat(name, ".txt"), "a+");

    printf("How many choice your want: ");
    scanf("%d", &choice_num);

    for (int i = 0; i < choice_num; i++)
    {
        printf("Enter %d choice: ", i + 1);
        scanf("%s", choice);
        fputs(strcat(choice, " 0"), poll_choice);
        fputs("\n", poll_choice);
    }

    fclose(poll_list);
    fclose(poll_choice);
    fclose(user_profile);
    fclose(user_list);
    admin_screen();
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
        number++;
    }

    rewind(poll_list);

    if (number == 1)
    {
        char create;
        printf("no poll found\n");
        printf("Do you want to create a new poll?(y/n): ");
        scanf(" %c", &create);
        if (create == 'y')
        {
            create_poll();
        }
        else
        {
            admin_screen();
        }
    }
    else
    {
        printf("\n\n+==============================+\n");
        printf("|    This is your poll list    |\n");
        printf("+==============================+\n");

        int i = 1;
        while (fgets(poll, 100, poll_list))
        {
            printf("%d) %s", i, poll);
            i++;
        }
    }

    rewind(poll_list);

    do
    {
        printf("\nEnter number : ");
        scanf("%d", &poll_number);
        printf("\n");
    } while (poll_number < 1 || poll_number > number - 1);

    number = 1;

    for (int i = 0; i < poll_number; i++)
    {
        fgets(poll, 100, poll_list);
    }

    poll[strlen(poll) - 1] = '\0';

    printf("Name : %s\n\n", poll);

    choice_list = fopen(strcat(poll, ".txt"), "r");

    while (fgets(choice, 100, choice_list))
    {
        number++;
    }

    int percent[number - 1];

    for (int i = 0; i < number - 1; i++)
    {
        percent[i] = 0;
    }

    rewind(choice_list);

    int count = 0;

    while (fgets(choice, 100, choice_list))
    {
        // printf("%lu", strlen(choice));
        for(int i = 0; i < strlen(choice); i++)
        {
            if (choice[i] == ' ')
            {
                for (int j = i + 1; j < strlen(choice) - 1; j++)
                {
                    percent[count] += (choice[j] - '0') * pow(10, (strlen(choice) - 2) - j);
                }
                choice[i] = '\0';
            }
        }
        printf("  %d) %s  ", count + 1, choice);


        count++;
    }

    int status = percentage(percent, number - 1);

    printf("\n\n");

    if (status != 0)
    {
        for (int i = 10; i > 0; i--)
        {
            if(i == 10)
            {
                printf("%d%% |", i * 10);
            }
            else
            {
                printf("%d%%  |", i * 10);
            }
            
            for (int j = 0; j < number - 1; j++)
            {
                if (percent[j] >= i)
                {
                    printf("   ##");
                }
                else
                {
                    printf("     ");
                }
            }
            printf("   \n");
        }
        printf("      ");
        for (int i = 0; i < number - 1; i++)
        {
            printf("-----");
        }
        printf("---\n");
        printf("         ");

        for (int i = 0; i < number - 1; i++)
        {
            printf("%d    ", i + 1);
        }
        printf("\n");
    }
    else
    {
        printf("No one vote yet.\n");
    }

    char con;

    printf("Enter any key to continue: ");
    scanf(" %c", &con);

    fclose(poll_list);
    admin_screen();
}

int percentage(int *percent, int size)
{
    int sum = 0;
    for(int i = 0; i < size; i++)
    {
        sum += percent[i];
    }

    if (sum != 0)
    {
        for (int i = 0; i < size; i++)
        {
            percent[i] = (((percent[i] * 100) / sum) / 10) + 1;
        }
    }
    else
    {
        return 0;
    }
    return 1;
}