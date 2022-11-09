#include <stdio.h>

void poll();
int voter_screen()
{
    int option;
    printf("Please select one of this option\n");
    printf("1) View poll list\n");
    printf("2) Exit\n\n");

    printf("Enter your option: ");
    scanf("%d", &option);

    if (option == 1)
    {
        poll();
    }
    else if (option == 2)
    {
        printf("Thank you");
    }

    return 0;
}
void poll()
{
    FILE *poll_list;

    poll_list = fopen("poll_list.txt", "r");

    char poll[100];

    int number = 1;
    int poll_number;

    printf("+==============================+\n");
    printf("|    This is your poll list    |\n");
    printf("+==============================+\n");

    while (fgets(poll, 100, poll_list))
    {
        printf("%d) %s", number, poll);
        number++;
    }

    number = 1;
    fclose(poll_list);
}