#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define MAX_LINE_LENGTH 1000

int login()
{
    FILE *user_name;
    FILE *pass_word;
    char user[MAX_LINE_LENGTH];
    char pass[MAX_LINE_LENGTH];
    char username[MAX_LINE_LENGTH];
    char password[MAX_LINE_LENGTH];
    int id = 1;
    int role;

    user_name = fopen("user.txt", "r");
    pass_word = fopen("password.txt", "r");

    while(true)
    {
        printf("Username: ");
        scanf("%s", username);
        printf("Password: ");
        scanf("%s", password);

        while (fgets(user, MAX_LINE_LENGTH, user_name))
        {
            for (int i = 0; i < MAX_LINE_LENGTH; i++)
            {
                user[i] = user[i];
                if (user[i] == ' ')
                {
                    role = user[i + 1];
                    user[i] = '\0';
                    break;
                }
            }
            
            if (strcmp(user, username) == 0)
            {
                for (int i = 0; i < id; i++)
                {
                    fgets(pass, MAX_LINE_LENGTH, pass_word);
                }
                pass[strlen(pass) - 1] = '\0';

                if (strcmp(pass, password) == 0)
                {
                    printf("\n\nLogin successful!!\n");
                    fclose(user_name);
                    fclose(pass_word);
                    return id;
                }
                else
                {
                    break;
                }
            }
            id++;
        }

        printf("Your username or password is incorrect\n");
        rewind(user_name);
        rewind(pass_word);
        id = 1;
    }

    fclose(user_name);
    fclose(pass_word);
    return 0;
}