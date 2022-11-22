#include <stdio.h>
#include <string.h>

void poll(int id);
void voting(int poll_number);

int voter_screen(int id)
{
    poll(id);

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
        voting(poll_number);
    }

    fclose(poll_list);
    fclose(username);
    fclose(done);
}

void voting(int poll_number)
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
}
