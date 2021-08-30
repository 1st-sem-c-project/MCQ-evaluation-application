#include"question_store.h"
#include<time.h>
#include<stdlib.h>
#include<stdio.h>
void get_question(struct Question *question){// get the question in the structure in the structure availabe in the gui
    int total_question;
    FILE *fptr;
    int questionNumber ;
    time_t t;
    FILE *numberFile = fopen("resources/question_user_number.txt","r");
    fscanf(numberFile,"%d",&total_question);
    fclose(numberFile);
    
    srand(time(&t));
    questionNumber = rand()%(total_question+1);
    
    fptr = fopen("resources/question.txt","rb");
    for (int i = 0; i < questionNumber; i++)
    {
        fread(question,sizeof(struct Question),1,fptr);
    }
    
    fclose(fptr);
}