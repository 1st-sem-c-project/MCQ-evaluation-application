#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <stdlib.h>
#include "emailValidation.h"
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
    int emailValidation = emailValidate(reg.email);
    if(emailValidation == 0){
        return 0;
    }

    // open file for writing
    user = fopen("resources/username_password.txt", "ab");
    if (user == NULL)
    {
        fprintf(stderr, "\nError opend file\n");
        exit(1);
    }

  
   

   
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
    char firstname[20], text[7],resources [100], filepath[100];
    FILE *userlogin;
    strcpy(firstname, reg.firstname);
    strcpy(text, ".txt");
    strcpy(resources, "resources/");
    strcat(resources, firstname);
    strcat(resources,text);
    strcpy(filepath, resources);
            
    userlogin =fopen(filepath,"w");
    fwrite(&reg, sizeof(reg), 1, userlogin);
    if (fwrite != 0)
        {
        printf("Contents to file written successfully !\n");
        }
    else {
     printf("Error writing file !\n");
     }
 
    fclose(userlogin);
    return 0;
}
