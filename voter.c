#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void poll(int id);
void voting(int poll_number, int id);

int voter_screen(int id)
{
    int choice;

    printf("\n\n1) Voting\n");
    printf("2) Quit\n\n");

    do
    {
        printf("Enter your choice: ");
        scanf("%d", &choice);
    } while (choice != 1 && choice != 2);

    if (choice == 1)
    {
        poll(id);
    }
    if (choice == 2)
    {
        return 0;
    }

    return 0;
}

void poll(int id)
{
    FILE *poll_list;

    //Check if user is already vote

    FILE *username;

    FILE *done;

    username = fopen("user.txt", "r");

    char user[1000];

    for (int i = 0; i < id; i++)
    {
        fgets(user, 1000, username);
    }

    for (int i = 0; i < 1000; i++)
    {
        user[i] = user[i];
        if (user[i] == ' ')
        {
            user[i] = '\0';
            break;
        }
    }

    done = fopen(strcat(user, ".txt"), "r");

    poll_list = fopen("poll_list.txt", "r");

    char poll[100];

    int number = 1;
    int poll_number;

    printf("\n\n+==============================+\n");
    printf("|          Poll list           |\n");
    printf("+==============================+\n");

    while (fgets(poll, 100, poll_list))
    {
        printf("%d) %s", number, poll);
        number++;
    }

    number = 1;
    char check_vote[10];

    printf("Enter what poll do you want to vote: ");
    scanf("%d", &poll_number);

    for (int i = 0; i < poll_number; i++)
    {
        fgets(check_vote, 1000, done);
    }

    rewind(done);

    if (check_vote[0] == '1')
    {
        char con;
        printf("\n\n+--------------------------------------------------------+\n");
        printf("|                You already vote is poll                |\n");
        printf("+--------------------------------------------------------+\n");
        printf("\nEnter any key to continue: ");
        scanf(" %c", &con);
        voter_screen(id);
    }
    else if (check_vote[0] == '0')
    {
        voting(poll_number, id);
    }

    fclose(poll_list);
    fclose(username);
    fclose(done);
}

void voting(int poll_number, int id)
{
    FILE *poll_list;
    FILE *choice_list;

    poll_list = fopen("poll_list.txt", "r");

    char poll[100];
    char choice[100];

    for (int i = 0; i < poll_number; i++)
    {
        fgets(poll, 100, poll_list);
    }

    poll[strlen(poll) - 1] = '\0';

    choice_list = fopen(strcat(poll, ".txt"), "r");

    int count = 1;

    while (fgets(choice, 100, choice_list))
    {
        for(int i = 0; i < strlen(choice); i++)
        {
            if (choice[i] == ' ')
            {
                choice[i] = '\0';
            }
        }

        printf("%d) %s\n", count, choice);
        count++;
    }

    rewind(choice_list);

    int select;
    char score_str[100];
    int score;

    printf("Enter number you what to vote: ");
    scanf("%d", &select);

    for (int i = 0; i < select; i++)
    {
        fgets(choice, 100, choice_list);
    }

    for (int i = 0; i < strlen(choice); i++)
    {
        if (choice[i] == ' ')
        {
            int x = 0;
            for (int j = i + 1; j < strlen(choice); j++)
            {
                if (choice[j] != '\n')
                {
                    score_str[x] = choice[j];
                    x++;
                }
                else
                {
                    score_str[x] = '\0';
                }
            }
            choice[i] = '\0';
            break;
        }
    }
    score = atoi(score_str);

    score++;


    sprintf(score_str, "%d", score);

    strcat(choice, " ");
    strcat(choice, score_str);

    strcpy(score_str, choice);

    rewind(choice_list);

    char update[1000];

    update[0] = '\0';

    count = 1;

    while (fgets(choice, 100, choice_list))
    {
        if (count == select)
        {
            strcat(update, score_str);
            strcat(update, "\n");
        }
        else
        {
            strcat(update, choice);
        }

        count++;
    }

    fclose(choice_list);

    choice_list = fopen(poll, "w");

    fprintf(choice_list, "%s", update);
    fclose(choice_list);

    FILE *user_update;
    FILE *user_profile;

    user_profile = fopen("user.txt", "r");

    char username[100];

    for(int i = 0; i < id; i++)
    {
        fgets(username, 100, user_profile);
    }

    username[strlen(username) - 3] = '\0';

    user_update = fopen(strcat(username, ".txt"), "r");

    count = 0;

    char temp[100];

    while (fgets(temp, 100, user_update))
    {
        count++;
    }

    char flag[count][3];

    rewind(user_update);

    int i = 0;

    while (fgets(flag[i], 100, user_update))
    {
        flag[i][1] = '\0';
        i++;
    }

    flag[poll_number - 1][0] = '1';

    char flag_update[1000];

    flag_update[0] = '\0';

    for(int i = 0; i < count; i++)
    {
        strcat(flag_update, flag[i]);
        strcat(flag_update, "\n");
    }

    fclose(user_update);

    user_update = fopen(username, "w");

    fprintf(user_update, "%s", flag_update);

    fclose(user_update);

    voter_screen(id);
}
