#include <stdio.h>
#include <string.h>
#include <stdlib.h>


char* replaceword(const char* str, const char* oldword, const char* newword) {
    char* resultstring;
    int i, count = 0;
    int newWordLength = strlen(newword);
    int oldWordLength = strlen(oldword);

    
    for (i = 0; str[i] != '\0'; i++) {
        if (strstr(&str[i], oldword) == &str[i]) {
            count++;
            i = i + oldWordLength - 1;
        }
    }

    
    resultstring = (char*)malloc(i + count * (newWordLength - oldWordLength) + 1);
    if (resultstring == NULL) {
        printf("Memory allocation failed.\n");
        exit(1);
    }

    i = 0;
    while (*str) {
        if (strstr(str, oldword) == str) {
            strcpy(&resultstring[i], newword);
            i += newWordLength;
            str += oldWordLength;
        } else {
            resultstring[i++] = *str++;
        }
    }
    resultstring[i] = '\0';
    return resultstring;
}

int main() {
    FILE* ptr1 = NULL;
    FILE* ptr2 = NULL;
    ptr1 = fopen("bill.txt", "r");
    ptr2 = fopen("genbill.txt", "w");

    if (ptr1 == NULL || ptr2 == NULL) {
        printf("Error opening files.\n");
        return 1;
    }

    char str[200];
    fgets(str, 200, ptr1);
    printf("THE GIVEN BILL TEMPLATE WAS : %s\n", str);

    char* newstr;
    char* temp;

    
    newstr = replaceword(str, "{{item}}", "Table Fan");

    
    temp = replaceword(newstr, "{{outlet}}", "Ram Laxmi fan outlet");
    free(newstr);  
    newstr = temp;

    
    temp = replaceword(newstr, "{{name}}", "customer");
    free(newstr);
    newstr = temp;

    
    printf("THE ACTUAL GENERATED BILL TEMPLATE IS : %s\n", newstr);
    printf("THE GENERATED BILL HAS BEEN WRITTEN TO THE FILE genbill.txt\n");
    fprintf(ptr2, "%s", newstr);

    
    fclose(ptr1);
    fclose(ptr2);
    free(newstr);

    return 0;
}
