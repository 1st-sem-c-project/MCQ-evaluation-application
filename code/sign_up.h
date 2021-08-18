#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <stdlib.h>
struct Register
{
    char firstname[30];
    char lastname[30];
    char email[50];
    char username[30];
    char password[30];
    int total_answers;
    int correct_answers;
    int incorrect_answers;
    int score;
    int admin;
};

int registration(struct Register reg)
{
    // char email[100], password1[100], password2[100], validate[100];
    // char gmail[] = "@gmail.com";
    // char email1[] = "@email.com";
    FILE *user;

    // open file for writing
    user = fopen("resources/username_password.txt", "ab");
    if (user == NULL)
    {
        fprintf(stderr, "\nError opend file\n");
        exit(1);
    }

    // printf("Register for more challenges: \n");
    // printf("Enter name: \n");
    // scanf("%s", &reg.name);
    // printf("Enter email \n");
    // scanf("%s", &email);
    // int length = strlen(email);
    // int i = length-10, j = 0;
    // while (i < length)
    // {
    //     validate[j] = email[i];
    //     j++;
    //     i++;
    // }
    // int result = strcmp(validate, email1);
    // int result1 = strcmp(validate, gmail);

    // if (result == 0 || result1 == 0){
    //     strcpy(reg.email, email);

    //     printf("Enter password \n");
    //     scanf("%s", &password1);
    //     printf("Enter password once again to confirm \n");
    //     scanf("%s", &password2);
    //     if (strcmp(password1, password2) == 0)
    //     {
    //         strcpy(reg.password, password1);
    //         printf("User registered successfully \n");
    //     }
    //     else
    //     {
    //         printf("Password and confirm password doesnot match!\n");
    //     }
    // }
    // else
    // {
    //     printf("Email should contain @gmail.com or @email.com \n");
    // }
    // write struct to file
    fwrite(&reg, sizeof(reg), 1, user);

    if (fwrite != 0)
    {
        printf("Contents to file written successfully !\n");
        FILE *numberptr,*tempfile;
        numberptr = fopen("resources/question_user_number.txt","rb");
        tempfile = fopen("resources/temp.txt","wb");
        int question_number;
        int user_number;
        fscanf(numberptr,"%d %d",&question_number,&user_number);
        user_number++;
        fprintf(tempfile,"%d %d",question_number,user_number);
        fclose(numberptr);
        fclose(tempfile);
        remove("resources/question_user_number.txt");
        rename("resources/temp.txt","resources/question_user_number.txt");

    }
    else
        printf("Error writing file !\n");

    // close file
    fclose(user);
    return 0;
}
