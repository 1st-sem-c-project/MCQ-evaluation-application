void store_in_database(struct Register user){
    FILE *auser = fopen("resources/active_user.txt","w");
    fwrite(&user,sizeof(struct Register),1,auser);
    fclose(auser);
}
void get_student_data(struct Register *student,int *position){
    FILE *fptr = fopen("resources/question_user_number.txt","rb");
    int totalStudents;
    int totalQuestion;
    fscanf(fptr,"%d %d",&totalQuestion,&totalStudents);
    fclose(fptr);
    fptr = fopen("resources/username_password.txt","r");
    for (int i = 0; i < *position; i++)
    {
        fread(student,sizeof(struct Register),1,fptr);
        if((*student).admin == 1){
            if (*position == totalStudents){
                rewind(fptr);
                *position = 1;
            }
            fread(student,sizeof(struct Register),1,fptr);
            (*position)++;
        }
    }
    fclose(fptr);
    (*position)++;
    if(*position>totalStudents){
        *position = 1;
    }
}
void change_filename(){
    int removed = remove("resources/username_password.txt");
    printf("\n\n%d\n\n",removed);
    if(removed == 0){
        rename("resources/active_user.txt","resources/username_password1.txt");
    }else{
        printf("not renamed!");
    }
}