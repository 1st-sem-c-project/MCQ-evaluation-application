#include <stdio.h>
FILE *ptr=fopen ("qsn.txt", "rb");
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