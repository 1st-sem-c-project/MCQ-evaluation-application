#include <stdio.h>
#include <string.h>
 
int logout(char *firstname1) {
        char firstname[20], text[7],resources [100], filepath[100];
        strcpy(firstname, firstname1);
        strcpy(text, ".txt");
        strcpy(resources, "resources/");
        strcat(resources, firstname);
        strcat(resources,text);
        strcpy(filepath, resources);
        printf("filepath");
    if (remove(filepath) == 0) {
        printf("The file is deleted successfully.");
    } else {
        printf("The file is not deleted.");
    }
    return 0;
}
