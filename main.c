#include <stdio.h>
#include "system.c"
#include "admin.c"
#include "voter.c"


int main()
{
    // printf("%d\n", login());
    int role = login();

    printf("%d\n", role);

    if (role == 1)
    {
        int num = admin_screen();
    }
    else if (role == 0)
    {
        return 1;
    }

    return 0;
}