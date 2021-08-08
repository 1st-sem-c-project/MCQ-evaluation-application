#include<stdio.h>
struct Question{
    char question[300];
    char options[4][50];
    char correct[50];
};

void store_to_the_database(struct Question question){
    FILE *ptr;
    ptr=fopen("resources/question.txt", "ab");
    fwrite(&question, sizeof(question), 1, ptr);
    fclose(ptr);

}