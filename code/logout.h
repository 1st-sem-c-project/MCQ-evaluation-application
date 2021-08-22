#include <stdio.h>
#include <string.h>
 
int logout() {
        
    if (remove("resources/active_user.txt") == 0) {
        printf("The file is deleted successfully.");
    } else {
        printf("The file is not deleted.");
    }
    return 0;
}
