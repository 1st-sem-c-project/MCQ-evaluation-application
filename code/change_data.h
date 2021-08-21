void store_in_database(struct Register user){
    FILE *auser = fopen("resources/active_user.txt","w");
    fwrite(&user,sizeof(struct Register),1,auser);
    fclose(auser);
}