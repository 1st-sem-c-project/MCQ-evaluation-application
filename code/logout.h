#include <stdio.h>
#include <string.h>
 
int logout(struct Register user) {
  
    int question_number,user_number;
    FILE *active_user = fopen("resources/active_user.txt","ab");
    FILE *main_database = fopen("resources/username_password.txt","rb");
   struct Register userdata ;
    
  while (fread(&userdata, sizeof(struct Register), 1, main_database))
    {
        if(strcmp(userdata.email, user.email) != 0){
            fwrite(&userdata, sizeof(struct Register), 1, active_user);
        }
        
    }

  
    fclose(active_user);
    fclose(main_database);
    return 0;
}
