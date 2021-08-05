#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <stdlib.h>
struct Register
{
    char name[100];
    char email[100];
    char password[100];

} reg;

int Register()
{
    char email[100], password1[100], password2[100], validate[100];
    char gmail[] = "@gmail.com";
    char email1[] = "@email.com";
    FILE *user;
      
    // open file for writing
    user = fopen ("user.dat", "w");
    if (user == NULL)
    {
        fprintf(stderr, "\nError opend file\n");
        exit (1);
    }

    printf("Register for more challenges: \n");
    printf("Enter name: \n");
    scanf("%s", &reg.name);
    printf("Enter email \n");
    scanf("%s", &email);
    int length = strlen(email);
    int i = length-10, j = 0;
    while (i < length)
    {
        validate[j] = email[i];
        j++;
        i++;
    }
    int result = strcmp(validate, email1);
    int result1 = strcmp(validate, gmail);
  
    if (result == 0 || result1 == 0){
        strcpy(reg.email, email);

        printf("Enter password \n");
        scanf("%s", &password1);
        printf("Enter password once again to confirm \n");
        scanf("%s", &password2);
        if (strcmp(password1, password2) == 0)
        {
            strcpy(reg.password, password1);
            printf("User registered successfully \n");
        }
        else
        {
            printf("Password and confirm password doesnot match!\n");
        }
    }
    else
    {
        printf("Email should contain @gmail.com or @email.com \n");
    }
     // write struct to file
    fwrite (&reg, sizeof(struct Register), 1, user);
   

      
    if(fwrite != 0) 
        printf("Contents to file written successfully !\n");
    else 
        printf("Error writing file !\n");
  
    // close file
    fclose (user);
    return 0;
}