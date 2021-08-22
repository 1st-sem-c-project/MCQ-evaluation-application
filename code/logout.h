#include <stdio.h>
#include <string.h>
 
int logout(char *firstname1) {
    char firstname[20], text[7],resources [100], filepath[100];
        
    if (remove("resources/active_user.txt") == 0) {
        printf("The file is deleted successfully.");
    } else {
        printf("The file is not deleted.");
    }
    return 0;
}
