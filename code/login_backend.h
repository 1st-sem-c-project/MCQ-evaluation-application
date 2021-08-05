// C program for writing 
// struct to file
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
  
// a struct to read and write
struct Login
{
    char name[100];
    char email[100];
    char password[100];

} ;
  
int login ()
{
    char email[100], password[100];

    FILE *login;
    struct Login input;
      
    // Open person.dat for reading
    login = fopen ("user.dat", "r");
    if (login == NULL)
    {
        fprintf(stderr, "\nError opening file\n");
        exit (1);
    }

    printf("Enter email: ");
    scanf("%s", &email);
    printf("Enter password: ");
    scanf("%s", &password);
    // read file contents till end of file
    while(fread(&input, sizeof(struct Login), 1, login)){
        int result =strcmp(email, input.email);
        int result1 =strcmp(password, input.password);
        if(result== 0 && result1 ==0) {

            printf("Login successfull \n");
            printf("Welcome %s", input.name);
        } else{
            printf("please register to login\n");
        }
    }
        
    // close file
    fclose (login);
  
    return 0;
}