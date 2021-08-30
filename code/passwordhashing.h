#include <stdio.h>
#include <string.h>
#include <math.h>

int passwordEncoder(char *password1, char *returnvalue){// this function hashes the password in simple manner
   
    char word[100] = "7782jka9jd02qe93id29930402sdw34kdfnd2je3kkxfajkdkadk";// random keyword
    
    char passwordhashed[1000] = "";

    int k =0, j =0, i=1;
    int length = strlen(password1);
    int length1 = strlen(word) + 1;

    for(i=1; i< length + length1; i++){
        if(i%3 == 0 && j < length && i!=1) {
            passwordhashed[i - 1] = password1[j];
            j++;
            
        } else{
            passwordhashed[i - 1] = word[k];
            k++;
        }
    }
     strcpy(returnvalue, passwordhashed);
    return 1;
}

