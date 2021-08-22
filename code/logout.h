#include <stdio.h>
#include <string.h>
 
int logout(struct Register user) {
  
    int question_number,user_number;
    FILE *active_user = fopen("resources/active_user.txt","ab");
    FILE *main_database = fopen("resources/username_password.txt","r");
    FILE *number_file = fopen("resources/question_user_number.txt","rb");
    fscanf(number_file,"%d %d",&question_number,&user_number);
    fclose(number_file);
    for (int i = 0; i < user_number-1; i++)
    {
        struct Register userdata ;
        fread(&userdata,sizeof(struct Register),1,main_database);
        if(i<user_number-1 && strcmp(userdata.username,user.username)==0){
            fread(&userdata,sizeof(struct Register),1,main_database);
        }
        fwrite(&userdata,sizeof(struct Register),1,active_user);
    }
    fclose(active_user);
    fclose(main_database);
    return 0;
}
