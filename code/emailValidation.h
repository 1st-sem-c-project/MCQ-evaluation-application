#include <stdio.h>
#include <string.h>
int emailValidate1(char *email){// checks if the email format is correct or not
    char validate[10];
    char gmail[] = "@gmail.com";
    char email1[] = "@email.com";
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
        return 1; 
} else return 0;
}