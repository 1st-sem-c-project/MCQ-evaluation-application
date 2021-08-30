#include<stdio.h>
struct Question{// universal structure to store question
    char question[300];
    char options[4][50];
    char correct[50];
};

void store_to_the_database(struct Question question)// store question to the data base
{
    FILE *ptr,*numberptr,*tempfile;
    ptr=fopen("resources/question.txt", "a");
    fwrite(&question, sizeof(question), 1, ptr);
    fclose(ptr);
    numberptr = fopen("resources/question_user_number.txt","rb");
    tempfile = fopen("resources/temp.txt","wb");
    int question_number;
    int user_number;
    fscanf(numberptr,"%d %d",&question_number,&user_number);
    question_number++;
    fprintf(tempfile,"%d %d",question_number,user_number);
    fclose(numberptr);
    fclose(tempfile);
    remove("resources/question_user_number.txt");
    rename("resources/temp.txt","resources/question_user_number.txt");
}