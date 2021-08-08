#include <stdio.h>
struct question {
    char qsn[100];
    char options [4] [100];
    char ans [100];
    
}s[2],st[4];
void main()
{
    FILE *ptr=fopen ("qsn.txt", "a+b");
    int i,j;
    char c;
    for (i=0;i<2;i++) {
    printf("Enter question ");
    scanf("%[^\n]s\n",s[i].qsn );
    getchar();
    printf("Enter the options ");
    for (j=0;j<4;j++) {
        scanf("%[^\n]s\n",s[i].options[j] );
        getchar();
    }
    printf("Correct answer :");
    scanf("%[^\n]s\n", s[i].ans);
    getchar();
}
fwrite (&s, sizeof(s), 2, ptr);
rewind (ptr);
fread (&st, sizeof(st), 4, ptr);
for (i=0;i<2;i++) {
    printf("%s\n", st[i].qsn);
    for (j=0;j<4;j++) {
        printf("%s \t", st[i].options[j]);
      
         
    }
    printf("\n%s\n", st[i].ans);
}

fclose(ptr);
}