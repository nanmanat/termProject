#include <stdio.h>
#include "system.c"
#include "admin.c"
#include "voter.c"


int main()
{
    int id = login();
    int role;

    FILE *username;

    username = fopen("user.txt", "r");

    char user[1000];

    for (int i = 0; i < id; i++)
    {
        fgets(user, 1000, username);
    }

    for (int i = 0; i < 1000; i++)
    {
        if (user[i] == ' ')
        {
            role = user[i + 1] - 48;
            user[i] = '\0';
            break;
        }
    }

    if (role == 1)
    {
        int num = admin_screen();
    }
    else if (role == 0)
    {
        int num = voter_screen(id);
    }

    return 0;
}