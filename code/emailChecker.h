#include <stdio.h>
#include <string.h>


int emailChecker (char *email){
    FILE *checkemail;
    struct Register input;
    // Open resources/username_password.txt for reading
    checkemail = fopen("resources/username_password.txt", "r");
    if (checkemail == NULL)
    {
        fprintf(stderr, "\nError opening file\n");
        exit(1);
    }

    // read file contents till end of file

    while (fread(&input, sizeof(struct Register), 1, checkemail))
    {
        int result = strcmp(email, input.email);
        if(result == 0) {
            printf("User with this email already registered");
            return 0;
        } 
    }
    
    fclose(checkemail);
    return 1;
}
    