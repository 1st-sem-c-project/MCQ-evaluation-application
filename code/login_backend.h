// C program for writing 
// struct to file
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sign_up.h"

// a struct to read and write
  
int login(char *email, char *password, struct Register *user)
{
    

    FILE *login;
    struct Register input;
    

   
      
    // Open person.dat for reading
    login = fopen ("resources/username_password.txt", "r");
    if (login == NULL)
    {
        fprintf(stderr, "\nError opening file\n");
        exit (1);
    }

    // read file contents till end of file
    while(fread(&input, sizeof(struct Register), 1, login)){
        
        int result =strcmp(email, input.email);

        int result1 =strcmp(password, input.password);
        printf("%d %d", result1, result);
        char firstname[20], text[7],resources [100], filepath[100];

        if(result== 0 && result1 ==0) {
            FILE *userlogin;
            printf("Hello world");
            
            strcpy(user->firstname, input.firstname);
            strcpy(user->lastname, input.lastname);
            strcpy(user->email, input.email);
            strcpy(user->username, input.username);
            strcpy(user->password, input.password);
            (*user).total_answers = input.total_answers;
            (*user).correct_answers = input.correct_answers;
            (*user).incorrect_answers = input.incorrect_answers;
            (*user).score = input.score;
            (*user).admin = input.admin;

            
            
            userlogin =fopen("resources/active_user.txt","w");
            fwrite(&input, sizeof(struct Register), 1, userlogin);
             if (fwrite != 0)
                {
                    printf("Contents to file written successfully !\n");
            }
             else {
                 printf("Error writing file !\n");
             }
             printf("Login successfulll");
            
             fclose(userlogin);
              return 1;
             break;
                
        } 
        

       
    }
    printf("please register to login\n");
    return 0;
        
        
    // close file
    fclose (login);
  
    return 0;
}