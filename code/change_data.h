#include <stdio.h>

void store_in_database(struct Register user)// stores students data in data base
{
    FILE *auser = fopen("resources/active_user.txt","w");
    fwrite(&user,sizeof(struct Register),1,auser);
    fclose(auser);
}
void get_student_data(struct Register *student,int *position)//read student data from the data base and stores it in structure
{
    FILE *fptr = fopen("resources/question_user_number.txt","rb");
    int totalStudents;
    int totalQuestion;
    fscanf(fptr,"%d %d",&totalQuestion,&totalStudents);
    fclose(fptr);
    fptr = fopen("resources/username_password.txt","r");
    for (int i = 0; i < *position; i++)
    {
        fread(student,sizeof(struct Register),1,fptr);
    }
    fclose(fptr);
    (*position)++;
    if(*position>totalStudents){
        *position = 1;
    }
}
void remove_filename() //changes the file names
{
    char filename[100] ="resources/username_password.txt";
    int removed = remove(filename);
    printf("\n\n%d\n\n",removed);
    if(removed == 0){
        int renamed =rename("resources/active_user.txt",filename);
        printf("       %d", renamed);
    }else{
        printf("not renamed!");
    }
}
