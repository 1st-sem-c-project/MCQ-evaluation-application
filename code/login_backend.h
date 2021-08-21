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
        char firstname[20], text[7],resources [100], filepath[100];

        if(result== 0 && result1 ==0) {
            FILE *userlogin;
            
            strcpy(user->firstname, input.firstname);
            strcpy(user->lastname, input.lastname);
            strcpy(user->email, input.email);
            strcpy(user->username, input.username);
            strcpy(user->password, input.password);
            strcpy(user->total_answers, input.total_answers);
            strcpy(user->correct_answers, input.correct_answers);
            strcpy(user->incorrect_answers, input.incorrect_answers);
            strcpy(user->score, input.score);
            strcpy(user->admin, input.admin);

            strcpy(firstname, input.firstname);
            strcpy(text, ".txt");
            strcpy(resources, "resources/");
            strcat(resources, firstname);
            strcat(resources,text);
            strcpy(filepath, resources);
            
            userlogin =fopen(filepath,"w");
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